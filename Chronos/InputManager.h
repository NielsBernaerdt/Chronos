#pragma once

enum class ControllerButton
{
	DPadUp = 0x0001,
	DPadDown = 0x0002,
	DPadLeft = 0x0004,
	DPadRight = 0x0008,
	ButtonStart = 0x0010,
	ButtonBack = 0x0020,
	LeftThumb = 0x0040,
	RightThumb = 0x0080,
	LeftShoulder = 0x0100,
	RightShoulder = 0x0200,
	ButtonA = 0x1000,
	ButtonB = 0x2000,
	ButtonX = 0x4000,
	ButtonY = 0x8000
};

class InputManager
{
	class InputManagerImpl;
	InputManagerImpl* m_pInputManagerImpl;

public:
	explicit InputManager(int controllerIndex);
	~InputManager();
	InputManager(const InputManager& other) = delete;
	InputManager(InputManager&& other) noexcept = delete;
	InputManager& operator=(const InputManager& other) = delete;
	InputManager& operator=(InputManager&& other) noexcept = delete;
	//
	void SetUpInput();
	bool ProcessInput();
	void HandleInput();
	bool IsPressed(ControllerButton button);
	//bool IsDown(ControllerButton button);
	//bool IsReleased(ControllerButton button);
};
