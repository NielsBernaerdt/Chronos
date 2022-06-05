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
	ControllerCommandsMap m_ConsoleCommands{};
	//KEYBOARD

	const Uint8* m_CurrentKeyboardState;
	const Uint8* m_PreviousKeyboardState;

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
		m_CurrentKeyboardState = SDL_GetKeyboardState(NULL);

		//GAMEPAD
		CopyMemory(&m_PreviousGamepadState, &m_CurrentGamepadState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentGamepadState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentGamepadState);

		auto buttonChanges = m_CurrentGamepadState.Gamepad.wButtons ^ m_PreviousGamepadState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentGamepadState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentGamepadState.Gamepad.wButtons);

		return !(m_CurrentGamepadState.Gamepad.wButtons & XINPUT_GAMEPAD_START);
	}
	bool Pressed(unsigned int button) const
	{
		return (m_ButtonsPressedThisFrame & button);
	}
	bool Down(unsigned int button) const
	{
		return (m_CurrentGamepadState.Gamepad.wButtons & button);
	}
	bool Released(unsigned int button) const
	{
		return (m_ButtonsReleasedThisFrame & button);
	}
	void Handle() const
	{
		for (const auto& e : m_ConsoleCommands)
		{
			if (Down(static_cast<unsigned int>(e.first)))
				e.second->Execute();
		}
	}
	void CommandToButton(ControllerButton button, std::unique_ptr<BCommand> command)
	{
		m_ConsoleCommands.insert(std::make_pair<>(button, std::move(command)));
	}
	void Pawn(GameObject* pPawn)
	{
		m_pPawn = pPawn;
		for(const auto& e : m_ConsoleCommands)
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
void InputManager::SetPawn(GameObject* pPawn) const
{
	m_pInputManagerImpl->Pawn(pPawn);
}