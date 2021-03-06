#pragma once
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include <string>
#include <memory>

#include "AudioManager.h"
#include "CBurgerIngredient.h"
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
	std::vector<glm::vec3> m_BurgerLocations;
	std::vector<Ingredient> m_BurgerIngredients;
	std::vector<glm::vec3> m_NPCLocations;

	void DetermineObjectsLocations();
	bool ReadFromFile();
	void CreateLevel(Scene& scene);
	void CreateNPCs(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreatePlayerPawns(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreateGameplayObjects(Scene& scene, std::shared_ptr<GameState> pObserver);
	void CreateTerrainLevel0(Scene& scene);
	void CreateTerrainLevel1(Scene& scene);
	void CreateTerrainLevel2(Scene& scene);

public:
	bool SetupLevelLayout(Scene& scene) override {
		bool exitGame = ReadFromFile();
		if (exitGame) return true;
		DetermineObjectsLocations();
		CreateLevel(scene);
		AudioManager::GetInstance().PlaySound("BackgroundMusic.wav", 10, 999);
		return false;
	}
	InputManager* ConfigureInput() override;
};
