#pragma once
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include <string>
#include <memory>
#include "Game.h"
#include "rapidjson/document.h"
#include "AudioManager.h"

class GameObject;
class GameState;

class Tron : public Game
{
private:
	bool ReadFromFile();
	void CreateScenes();
	void PrintStartMessage();
	static bool ParseJSON(const char* fileName, rapidjson::Document& jsonDoc);

	std::string m_GameMode{"Singleplayer"};
	static int m_NrEnemies;
	static std::shared_ptr<GameObject> m_pPlayerOnePawn;
	static std::shared_ptr<GameObject> m_pPlayerTwoPawn;

public:
	void CreatePawns();
	static void LoadSceneByIndex(int index);
	static void LoadScoreMenu();

	bool SetupGameScenes() override {
		const bool invalidFile = ReadFromFile();
		if (invalidFile) return true;
		PrintStartMessage();
		AudioManager::GetInstance().PlaySound("AudioFiles/BackgroundMusic.wav", 10, 999);
		return false;
	}
	InputManager* ConfigureInput() override;
};
