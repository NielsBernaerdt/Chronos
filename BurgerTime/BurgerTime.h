#pragma once
#include "Game.h"

class GameObject;

class BurgerTime : public Game
{
private:
	void SandboxScene(Scene& scene);

	GameObject* m_pPlayerOnePawn = nullptr;
	GameObject* m_pPlayerTwoPawn = nullptr;

public:
	void SetupObjects(Scene& scene) override {
		SandboxScene(scene);
	}
	std::vector<InputManager*> ConfigureInput() override;
};
