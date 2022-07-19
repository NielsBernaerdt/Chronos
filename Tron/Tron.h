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
	bool ReadFromFile();
	void CreateScenes();

public:
	static std::shared_ptr<GameObject> m_pPlayerOnePawn;

	void CreatePawns();
	static void CreateSceneByIndex(int index);
	static void CreateScene0();
	static void CreateScene1();
	static void CreateScene2();

	bool SetupGameScenes() override {
		const bool invalidFile = ReadFromFile();
		if (invalidFile) return true;
		return false;
	}
	InputManager* ConfigureInput() override;
};
