#pragma once
#include "Game.h"

class GameObject;

class BurgerTime : public Game
{
private:
	void TutorialScene(Scene& scene);
	void SceneGraphTestScene(Scene& scene) const;
	void ObserverScene(Scene& scene) const;	

	GameObject* m_pPlayerPawn = nullptr;

public:
	void SetupObjects(Scene& scene) override {
		TutorialScene(scene);
	}
	void ConfigureInput(InputManager* input) override;
};
