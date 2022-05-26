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
	std::unique_ptr<GameObject> m_pJerry;

	using ControllerCommandsMap = std::map<ControllerButton, Command*>;
	ControllerCommandsMap m_ConsoleCommands{};

public:
	explicit InputManagerImpl(int controllerIndex)
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
	//
	void SetUp()
	{
		Fire* testFire = new Fire(m_pJerry.get());
		std::pair<ControllerButton, Command*> test = std::make_pair<>(ControllerButton::ButtonA, testFire);
		m_ConsoleCommands.emplace(test);
	}
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
		return (m_CurrentState.Gamepad.wButtons & button);
	}
	bool Down(unsigned int button) const
	{
		return (m_ButtonsPressedThisFrame & button);
	}
	bool Released(unsigned int button) const
	{
		return (m_ButtonsReleasedThisFrame & button);
	}
	void Handle()
	{
		for (const auto& e : m_ConsoleCommands)
		{
			if (Released(static_cast<unsigned int>(e.first)))
				e.second->Execute();
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

void InputManager::SetUpInput()
{
	m_pInputManagerImpl->SetUp();
}
bool InputManager::ProcessInput()
{
	return m_pInputManagerImpl->Process();
}
void InputManager::HandleInput()
{
	m_pInputManagerImpl->Handle();
}