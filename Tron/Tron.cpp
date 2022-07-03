#include "Tron.h"
#include <InputManager.h>

bool Tron::ReadFromFile()
{
	return false;
}

void Tron::CreateLevel(Scene& /*scene*/)
{
}

void Tron::CreatePlayerPawns(Scene& /*scene*/, std::shared_ptr<GameState> /*pObserver*/)
{
}

void Tron::CreateNPCs(Scene& /*scene*/, std::shared_ptr<GameState> /*pObserver*/)
{
}

void Tron::CreateGameplayObjects(Scene& /*scene*/, std::shared_ptr<GameState> /*pObserver*/)
{
}

void Tron::CreateTerrainLevel0(Scene& /*scene*/)
{
}

InputManager* Tron::ConfigureInput()
{
	InputManager* inputManager = new InputManager{};

	return inputManager;
}