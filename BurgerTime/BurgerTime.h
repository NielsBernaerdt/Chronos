#pragma once
#include <string>
#include <memory>
#include "Game.h"

class GameObject;
class GameState;

class BurgerTime : public Game
{
private:
	GameObject* m_pPlayerOnePawn = nullptr;
	GameObject* m_pPlayerTwoPawn = nullptr;

	//LEVEL LAYOUT PARAMETERS
	int m_Map{0};
	std::string m_GameMode{"Versus"};
	int m_NrEnemies{};
	int m_NrBurgerIngredients{};

	bool ReadFromFile();
	void CreateLevel(Scene& scene);
	void CreateNPCs(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreatePlayerPawns(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreateGameplayObjects(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreateTerrain(Scene& scene);

public:
	bool SetupLevelLayout(Scene& scene) override {
		bool exitGame = ReadFromFile();
		if (exitGame) return true;
		CreateLevel(scene);
		return false;
	}
	std::vector<InputManager*> ConfigureInput() override;
};
