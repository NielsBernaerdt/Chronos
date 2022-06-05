#pragma once
#include <memory>

#include "Game.h"

class GameObject;

class BurgerTime : public Game
{
private:
	void SandboxScene(Scene& scene);

	GameObject* m_pPlayerPawn = nullptr;

public:
	void SetupObjects(Scene& scene) override {
		SandboxScene(scene);
	}
	void ConfigureInput(InputManager* input) const override;
};
