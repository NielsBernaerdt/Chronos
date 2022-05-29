#pragma once

#include <memory>

class GameObject;
class Command;
enum class ControllerButton;

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
	bool ProcessInput();
	void HandleInput();
	void BindCommandToButton(ControllerButton button, std::unique_ptr<Command> command);
	void SetPawn(GameObject* pPawn);
};
