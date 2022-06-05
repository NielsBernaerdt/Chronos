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

	int m_ControllerIndex;
	GameObject* m_pPawn = nullptr;

	using ControllerCommandsMap = std::map<ControllerButton, std::unique_ptr<BCommand>>;
	ControllerCommandsMap m_ConsoleCommandsGP{};

	//KEYBOARD
	const Uint8* m_CurrentKeyboardState;
	const Uint8* m_PreviousKeyboardState;
	using KeyboardCommandsMap = std::map<int, std::unique_ptr<BCommand>>;
	KeyboardCommandsMap m_ConsoleCommandsKB{};

public:
	explicit InputManagerImpl(int controllerIndex = 0)
		:m_ControllerIndex{ controllerIndex }
	{
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
		while (SDL_PollEvent(&event)) {}
		m_CurrentKeyboardState = SDL_GetKeyboardState(NULL);

		//GAMEPAD
		CopyMemory(&m_PreviousGamepadState, &m_CurrentGamepadState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentGamepadState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentGamepadState);

		auto buttonChanges = m_CurrentGamepadState.Gamepad.wButtons ^ m_PreviousGamepadState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentGamepadState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentGamepadState.Gamepad.wButtons);

		return (!(m_CurrentGamepadState.Gamepad.wButtons & XINPUT_GAMEPAD_START)	//QUIT WITH GAMEPAD
		&& !m_CurrentKeyboardState[SDL_SCANCODE_ESCAPE]);							//QUIT WITH KEYBOARD
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
	void Handle() const
	{
		for (const auto& gp : m_ConsoleCommandsGP)
		{
			if (Down(static_cast<unsigned int>(gp.first)))
				gp.second->Execute();
		}
		for(const auto& kb : m_ConsoleCommandsKB)
		{
			if (Down(kb.first))
				kb.second->Execute();
		}
	}
	void CommandToButton(ControllerButton button, std::unique_ptr<BCommand> command)
	{
		m_ConsoleCommandsGP.insert(std::make_pair<>(button, std::move(command)));
	}
	void CommandToButton(int keyboardButton, std::unique_ptr<BCommand> command)
	{
		m_ConsoleCommandsKB.insert(std::make_pair<>(keyboardButton, std::move(command)));
	}
	void Pawn(GameObject* pPawn)
	{
		m_pPawn = pPawn;
		for(const auto& e : m_ConsoleCommandsGP)
		{
			e.second->SetOwner(pPawn);
		}
		for(const auto& e : m_ConsoleCommandsKB)
		{
			e.second->SetOwner(pPawn);
		}
	}
};
InputManager::InputManager(int controllerIndex)
	:m_pInputManagerImpl{new InputManagerImpl{controllerIndex}}
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
void InputManager::HandleInput() const
{
	m_pInputManagerImpl->Handle();
}
void InputManager::BindCommandToButton(ControllerButton button, std::unique_ptr<BCommand> command) const
{
	m_pInputManagerImpl->CommandToButton(button, std::move(command));
}
void InputManager::BindCommandToButton(int keyboardButton, std::unique_ptr<BCommand> command) const
{
	m_pInputManagerImpl->CommandToButton(keyboardButton, std::move(command));
}
void InputManager::SetPawn(GameObject* pPawn) const
{
	m_pInputManagerImpl->Pawn(pPawn);
}