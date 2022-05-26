#include "ChronosPCH.h"
#include "InputManager.h"
//
#define WIN32_LEAN_AND_MEAN
#include <map>
#include <Windows.h>
#include <Xinput.h>
#include "CommandsBase.h"
//

class InputManager::InputManagerImpl
{
private:
	XINPUT_STATE m_CurrentState{};
	XINPUT_STATE m_PreviousState{};

	WORD m_ButtonsPressedThisFrame{};
	WORD m_ButtonsReleasedThisFrame{};

	int m_ControllerIndex;
	GameObject* m_pPawn = nullptr;

	using ControllerCommandsMap = std::map<ControllerButton, std::unique_ptr<Command>>;
	ControllerCommandsMap m_ConsoleCommands{};

public:
	explicit InputManagerImpl(int controllerIndex = 0)
		:m_ControllerIndex{ controllerIndex }
	{
		ZeroMemory(&m_PreviousState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
	}
	~InputManagerImpl() = default;
	InputManagerImpl(const InputManagerImpl& other) = delete;
	InputManagerImpl(InputManagerImpl&& other) noexcept = delete;
	InputManagerImpl& operator=(const InputManagerImpl& other) = delete;
	InputManagerImpl& operator=(InputManagerImpl&& other) noexcept = delete;

	bool Process()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (~m_CurrentState.Gamepad.wButtons);

		return !(m_CurrentState.Gamepad.wButtons & XINPUT_GAMEPAD_START);
	}
	bool Pressed(unsigned int button) const
	{
		return (m_ButtonsPressedThisFrame & button);
	}
	bool Down(unsigned int button) const
	{
		return (m_CurrentState.Gamepad.wButtons & button);
	}
	bool Released(unsigned int button) const
	{
		return (m_ButtonsReleasedThisFrame & button);
	}
	void Handle()
	{
		for (const auto& e : m_ConsoleCommands)
		{
			if (Pressed(static_cast<unsigned int>(e.first)))
				e.second->Execute();
		}
	}
	void CommandToButton(ControllerButton button, std::unique_ptr<Command> command)
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

bool InputManager::ProcessInput()
{
	return m_pInputManagerImpl->Process();
}
void InputManager::HandleInput()
{
	m_pInputManagerImpl->Handle();
}
void InputManager::BindCommandToButton(ControllerButton button, std::unique_ptr<Command> command)
{
	m_pInputManagerImpl->CommandToButton(button, std::move(command));
}
void InputManager::SetPawn(GameObject* pPawn)
{
	m_pInputManagerImpl->Pawn(pPawn);
}