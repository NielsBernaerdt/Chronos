#include "Tron.h"
#include <InputManager.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <CRender.h>
#include <Scene.h>
#include <SDL_mouse.h>

#include "CTankTron.h"
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

	std::unique_ptr<CTankTron> tronCTankTron = std::make_unique<CTankTron>(tronTank.get());
	tronTank->AddComponent(std::move(tronCTankTron));

	scene.Add(tronTank);
	m_pPlayerOnePawn = tronTank.get();

	/////////////////TANKBARREL////////////////////
	const auto tronTankBarrel = std::make_shared<GameObject>(std::string{ "TronPawnOneBarrel" });
	tronTankBarrel->GetTransform()->SetPosition(22, 22);
	tronTankBarrel->GetTransform()->SetScale(40, 10);

	const auto tronBarrelTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> tronBarrelCRender = std::make_unique<CRender>(tronTankBarrel.get(), tronBarrelTexture, true);
	tronTankBarrel->AddComponent(std::move(tronBarrelCRender));

	scene.Add(tronTankBarrel);

	tronTankBarrel->SetParent(tronTank.get());
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

	//INPUT PAWN ONE
	inputManager->BindCommandToButton(ControllerButton::DPadRight, std::make_unique<MoveHorizontal>(true));
	inputManager->BindCommandToButton(ControllerButton::DPadLeft, std::make_unique<MoveHorizontal>(false));
	inputManager->BindCommandToButton(ControllerButton::DPadUp, std::make_unique<MoveVertical>(true));
	inputManager->BindCommandToButton(ControllerButton::DPadDown, std::make_unique<MoveVertical>(false));
	inputManager->BindCommandToButton(SDL_BUTTON_LMASK, std::make_unique<Shoot>());

	inputManager->AddController(0, m_pPlayerOnePawn);

	return inputManager;
}