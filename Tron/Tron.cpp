#include "Tron.h"
#include <InputManager.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <CRender.h>
#include <Scene.h>
#include "InputCommands.h"


bool Tron::ReadFromFile()
{
	return false;
}

void Tron::CreateLevel(Scene& scene)
{
	std::shared_ptr<GameState> temp;
	CreatePlayerPawns(scene, temp);
}

void Tron::CreatePlayerPawns(Scene& scene, std::shared_ptr<GameState> /*pObserver*/)
{
	const auto tronTank = std::make_shared<GameObject>(std::string{ "TronPawnOne" });
	tronTank->GetTransform()->SetPosition(0, 90);
	tronTank->GetTransform()->SetScale(44, 44);

	const auto tronTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankRed.png");
	std::unique_ptr<CRender> tronCRender = std::make_unique<CRender>(tronTank.get(), tronTexture, true);
	tronTank->AddComponent(std::move(tronCRender));

	scene.Add(tronTank);
	m_pPlayerOnePawn = tronTank.get();
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

	inputManager->BindCommandToButton(ControllerButton::DPadRight, std::make_unique<MoveRight>());
	inputManager->BindCommandToButton(ControllerButton::DPadLeft, std::make_unique<MoveLeft>());
	inputManager->BindCommandToButton(ControllerButton::DPadUp, std::make_unique<ClimbUp>());
	inputManager->BindCommandToButton(ControllerButton::DPadDown, std::make_unique<ClimbDown>());

	return inputManager;
}