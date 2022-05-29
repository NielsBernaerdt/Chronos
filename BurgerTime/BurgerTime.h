#pragma once
#include "Game.h"

class BurgerTime : public Game
{
private:
	void TutorialScene(Scene& scene) const;
	void SceneGraphTestScene(Scene& scene) const;
	void ObserverScene(Scene& scene) const;	

public:
	void SetupObjects(Scene& scene) override
	{
		ObserverScene(scene);
	};
	void ConfigureInput(InputManager* input) override;
};
