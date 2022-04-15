#include "ChronosPCH.h"
#include "InputManager.h"
//
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <Xinput.h>
#include "Commands.h"
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

	std::unique_ptr<Command> buttonX;
	std::unique_ptr<Command> buttonY;
	std::unique_ptr<Command> buttonA;
	std::unique_ptr<Command> buttonB;

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
		buttonA = std::unique_ptr<Jump>(std::make_unique<Jump>(m_pJerry.get()));
		buttonB = std::unique_ptr<Duck>(std::make_unique<Duck>(m_pJerry.get()));
		buttonX = std::unique_ptr<Fire>(std::make_unique<Fire>(m_pJerry.get()));
		buttonY = std::unique_ptr<Fart>(std::make_unique<Fart>(m_pJerry.get()));
	}
	bool Process()
	{
		CopyMemory(&m_PreviousState, &m_CurrentState, sizeof(XINPUT_STATE));
		ZeroMemory(&m_CurrentState, sizeof(XINPUT_STATE));
		XInputGetState(m_ControllerIndex, &m_CurrentState);

		auto buttonChanges = m_CurrentState.Gamepad.wButtons ^ m_PreviousState.Gamepad.wButtons;
		m_ButtonsPressedThisFrame = buttonChanges & m_CurrentState.Gamepad.wButtons;
		m_ButtonsReleasedThisFrame = buttonChanges & (m_CurrentState.Gamepad.wButtons);

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
bool InputManager::IsPressed(ControllerButton button)
{
	return m_pInputManagerImpl->Released(static_cast<unsigned int>(button));
	//return m_pInputManagerImpl->Pressed(button);
	//return m_pInputManagerImpl->Pressed(button);
}
void InputManager::HandleInput()
{
	//if (IsPressed(ControllerButton::ButtonY)) buttonY->Execute();
	//else if (IsPressed(ControllerButton::ButtonX)) buttonX->Execute();
	//else if (IsPressed(ControllerButton::ButtonA)) buttonA->Execute();
	//else if (IsPressed(ControllerButton::ButtonB)) buttonB->Execute();
}