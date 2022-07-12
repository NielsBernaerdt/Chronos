#pragma once
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include <string>
#include <memory>
#include "Game.h"

class GameObject;
class GameState;

class Tron : public Game
{
private:
	GameObject* m_pPlayerOnePawn = nullptr;
	GameObject* m_pPlayerTwoPawn = nullptr;

	bool ReadFromFile();
	void CreateScenes();

	void CreateScene0();
	void CreateScene1();
	void CreateScene2();

public:
	bool SetupGameScenes() override {
		const bool invalidFile = ReadFromFile();
		if (invalidFile) return true;
		return false;
	}
	InputManager* ConfigureInput() override;
};
