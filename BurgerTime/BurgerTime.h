#pragma once
#include "Game.h"

class GameObject;

class BurgerTime : public Game
{
private:
	void SandboxScene(Scene& scene);
	void SceneGraphTestScene(Scene& scene) const;
	void ObserverScene(Scene& scene) const;	

	GameObject* m_pPlayerPawn = nullptr;

public:
	void SetupObjects(Scene& scene) override {
		SandboxScene(scene);
	}
	void ConfigureInput(InputManager* input) override;
};
