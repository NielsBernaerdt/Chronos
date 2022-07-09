#include "ChronosPCH.h"
#include "InputManager.h"
//
#define WIN32_LEAN_AND_MEAN
#include <map>
#include <Windows.h>
#include <Xinput.h>
#include "BCommand.h"
//

class InputManager::InputManagerImpl
{
private:
	//GAMEPAD
	XINPUT_STATE m_CurrentGamepadState{};
	XINPUT_STATE m_PreviousGamepadState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	using ControllerCommandsMap = std::map<ControllerButton, std::unique_ptr<BCommand>>;
	ControllerCommandsMap m_ConsoleCommandsGP{};

	std::vector<GameObject*> m_pPawns;

	//KEYBOARD
	const Uint8* m_CurrentKeyboardState;
	using KeyboardCommandsMap = std::map<int, std::unique_ptr<BCommand>>;
	KeyboardCommandsMap m_ConsoleCommandsKB{};

	//MOUSE
	int m_MouseX{}, m_MouseY{};
	Uint32 m_CurrentMouseButtons{};
	using MouseCommandsMap = std::map<int, std::unique_ptr<BCommand>>;
	MouseCommandsMap m_ConsoleCommandsMouse{};

public:
	explicit InputManagerImpl()
	{
		// FILL PAWN ARRAY FOR MAX NUMBER USERS
		for(DWORD i = 0; i < XUSER_MAX_COUNT; ++i)
		{
			m_pPawns.push_back(nullptr);
		}
		//LAST ITEM == KEYBOARD
		m_pPawns.push_back(nullptr);

		ZeroMemory(&m_PreviousGamepadState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentGamepadState, sizeof(XINPUT_STATE));
	}
	~InputManagerImpl() = default;
	InputManagerImpl(const InputManagerImpl& other) = delete;
	InputManagerImpl(InputManagerImpl&& other) noexcept = delete;
	InputManagerImpl& operator=(const InputManagerImpl& other) = delete;
	InputManagerImpl& operator=(InputManagerImpl&& other) noexcept = delete;

	bool Process()
	{
		//KEYBOARD
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT) {
				return false;
			}
			if (event.type == SDL_KEYDOWN) {

			}
			if (event.type == SDL_MOUSEBUTTONDOWN) {

			}
		}
		m_CurrentKeyboardState = SDL_GetKeyboardState(NULL);

		//MOUSE
		m_CurrentMouseButtons = SDL_GetMouseState(&m_MouseX, &m_MouseY);

		//GAMEPAD
		for (int i{}; i < 4; ++i)
		{
			CopyMemory(&m_PreviousGamepadState, &m_CurrentGamepadState, sizeof(XINPUT_STATE));
			ZeroMemory(&m_CurrentGamepadState, sizeof(XINPUT_STATE));
			
			if (XInputGetState(i, &m_CurrentGamepadState) == ERROR_SUCCESS)
			{
				auto buttonChanges = m_CurrentGamepadState.Gamepad.wButtons ^ m_PreviousGamepadState.Gamepad.wButtons;
				m_ButtonsPressedThisFrame = buttonChanges & m_CurrentGamepadState.Gamepad.wButtons;
				m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentGamepadState.Gamepad.wButtons);
			}
			else
			{
				continue;
			}

			bool shouldExit = (!(m_CurrentGamepadState.Gamepad.wButtons & XINPUT_GAMEPAD_START)	//QUIT WITH GAMEPAD
				&& !m_CurrentKeyboardState[SDL_SCANCODE_ESCAPE]);								//QUIT WITH KEYBOARD
			if (shouldExit == false)
				return false;

			HandleGPInput(i);
		}
		HandleKBInput();
		return true;
	}
	bool Pressed(unsigned int button) const
	{
		return (m_ButtonsPressedThisFrame & button);
	}
	bool Pressed(int keyboardButton) const
	{
		return m_CurrentKeyboardState[keyboardButton];
	}
	bool Down(unsigned int button) const
	{
		return (m_CurrentGamepadState.Gamepad.wButtons & button);
	}
	bool Down(int keyboardButton) const
	{
		return m_CurrentKeyboardState[keyboardButton];
	}
	bool Released(unsigned int button) const
	{
		return (m_ButtonsReleasedThisFrame & button);
	}
	bool Released(int keyboardButton) const
	{
		return m_CurrentKeyboardState[keyboardButton];
	}
	void HandleGPInput(int currentControllerIdx) const
	{
		if (m_pPawns[currentControllerIdx] == nullptr)
			return;

		for (const auto& gp : m_ConsoleCommandsGP)
		{
			if (Down(static_cast<unsigned int>(gp.first)))
				gp.second->Execute(m_pPawns[currentControllerIdx]);
		}
	}
	void HandleKBInput() const
	{
		//KEYBOARD IS LAST INDEX - > pawns.back
		for (const auto& kb : m_ConsoleCommandsKB)
		{
			if (Down(kb.first))
				kb.second->Execute(m_pPawns.back());
		}
	}
	void HandleMouseButton() const
	{
		//KEYBOARD IS LAST INDEX - > pawns.back
		for(const auto& mb : m_ConsoleCommandsMouse)
		{
			if ((m_CurrentMouseButtons & mb.first) != 0)
				mb.second->Execute(m_pPawns.back());
		}
	}
	void CommandToButton(ControllerButton button, std::unique_ptr<BCommand> command)
	{
		m_ConsoleCommandsGP.insert(std::make_pair<>(button, std::move(command)));
	}
	void CommandToButton(int keyboardButton, std::unique_ptr<BCommand> command, bool isMouseButton)
	{
		if(isMouseButton)
		{
			m_ConsoleCommandsMouse.insert(std::make_pair<>(keyboardButton, std::move(command)));
		}
		else
		{
			m_ConsoleCommandsKB.insert(std::make_pair<>(keyboardButton, std::move(command)));
		}
	}
	void Pawn(int controllerIndex, GameObject* pPawn)
	{
		for(int i{}; i < m_pPawns.size(); ++i)
		{
			if (i == controllerIndex)
				m_pPawns[i] = pPawn;
		}
	}
	static const glm::vec2& MousePos()
	{
		if(this != nullptr)
		return glm::vec2{ m_MouseX, m_MouseY };
	}
};
InputManager::InputManager()
	:m_pInputManagerImpl{new InputManagerImpl{}}
{
}

InputManager::~InputManager()
{
	delete m_pInputManagerImpl;
}

bool InputManager::ProcessInput() const
{
	return m_pInputManagerImpl->Process();
}
void InputManager::BindCommandToButton(ControllerButton button, std::unique_ptr<BCommand> command) const
{
	m_pInputManagerImpl->CommandToButton(button, std::move(command));
}
void InputManager::BindCommandToButton(int keyboardButton, std::unique_ptr<BCommand> command, bool isMouseButton) const
{
	m_pInputManagerImpl->CommandToButton(keyboardButton, std::move(command), isMouseButton);
}
void InputManager::AddController(int controllerIndex, GameObject* pPawn) const
{
	m_pInputManagerImpl->Pawn(controllerIndex, pPawn);
}
const glm::vec2& InputManager::GetMousePos()
{
	return InputManagerImpl::MousePos();
}