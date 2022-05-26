#pragma once

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
};
