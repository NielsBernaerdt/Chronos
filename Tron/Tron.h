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
	void CreateLevel(Scene& scene);
	void CreateNPCs(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreatePlayerPawns(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreateGameplayObjects(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreateTerrainLevel0(Scene& scene);

public:
	bool SetupLevelLayout(Scene& scene) override {
		bool exitGame = ReadFromFile();
		if (exitGame) return true;
		CreateLevel(scene);
		return false;
	}
	InputManager* ConfigureInput() override;
};
