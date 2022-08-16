#include "Tron.h"
#include <InputManager.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <CRender.h>
#include <iostream>
#include <Scene.h>
#include <SDL_mouse.h>
#include <SDL_scancode.h>

#include "CCollisionBox.h"
#include "CDiamond.h"
#include "CHealth.h"
#include "CollisionGroups.h"
#include "CTankNPC.h"
#include "CTankTron.h"
#include "InputCommands.h"
#include <CText.h>
#include "CHUDElement.h"
#include "CPoints.h"

std::shared_ptr<GameObject> Tron::m_pPlayerOnePawn = nullptr;

bool Tron::ReadFromFile()
{
	//READ FILE, RETURN TRUE IF INVALID
	CreateScenes();
	return false;
}

void Tron::CreateScenes()
{
	SceneManager::GetInstance().CreateScene("Level0");
	SceneManager::GetInstance().CreateScene("Level1");
	SceneManager::GetInstance().CreateScene("Level2");
	SceneManager::GetInstance().CreateScene("Main Menu");
	SceneManager::GetInstance().CreateScene("Score Menu");
	CreatePawns();
	CreateScene0();
}

void Tron::CreatePawns()
{
#pragma region PlayerPawn
	const auto tronTank = std::make_shared<GameObject>(std::string{ "TronPawnOne" });
	tronTank->GetTransform()->SetPosition(150, 150);
	tronTank->GetTransform()->SetScale(44, 44);

	const auto tronTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankRed.png");
	std::unique_ptr<CRender> tronCRender = std::make_unique<CRender>(tronTank.get(), tronTexture, true);
	tronTank->AddComponent(std::move(tronCRender));

	std::unique_ptr<CTankTron> tronCTankTron = std::make_unique<CTankTron>(tronTank.get());
	tronTank->AddComponent(std::move(tronCTankTron));

	std::unique_ptr<CCollisionBox> tronCCollision = std::make_unique<CCollisionBox>(tronTank.get(), CollisionGroup::Pawn);
	tronTank->AddComponent(std::move(tronCCollision));

	std::unique_ptr<CPoints> tronCPoints = std::make_unique<CPoints>(tronTank.get());
	tronCPoints->SetPoints(300);
	tronTank->AddComponent(std::move(tronCPoints));

	std::unique_ptr<CHealth> tronCHealth = std::make_unique<CHealth>(tronTank.get(), 3);
	tronTank->AddComponent(std::move(tronCHealth));

	m_pPlayerOnePawn = tronTank;

	/////////////////TANKBARREL////////////////////
	const auto tronTankBarrel = std::make_shared<GameObject>(std::string{ "TronPawnOneBarrel" });
	tronTankBarrel->GetTransform()->SetPosition(22, 22);
	tronTankBarrel->GetTransform()->SetScale(40, 10);

	const auto tronBarrelTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> tronBarrelCRender = std::make_unique<CRender>(tronTankBarrel.get(), tronBarrelTexture, true);
	tronTankBarrel->AddComponent(std::move(tronBarrelCRender));

	tronTankBarrel->SetParent(m_pPlayerOnePawn.get(), tronTankBarrel);
#pragma endregion PlayerPawn
}

void Tron::CreateSceneByIndex(int index)
{
	switch (index)
	{
	case 0:
		CreateScene0();
		break;
	case 1:
		CreateScene1();
		break;
	case 2:
		CreateScene2();
		break;
	default:
		std::cout << "Incorrect given index\n";
		break;
	}
}

void Tron::CreateScene0()
{
	auto scene = SceneManager::GetInstance().GetScene(0);
	scene->SetActive(true);

#pragma region PlayerPawns
	if (m_pPlayerOnePawn)
	{
		scene->Add(m_pPlayerOnePawn);
		m_pPlayerOnePawn->GetTransform()->SetPosition(150, 150);
		scene->Add(m_pPlayerOnePawn->GetChildren()[0]);
	}
#pragma endregion PlayerPawns
	const auto playerHud = std::make_shared<GameObject>(std::string{ "playerHud" });
	playerHud->GetTransform()->SetPosition(200, 0);

	std::unique_ptr<CText> hudText = std::make_unique<CText>(playerHud.get(), "HelloWorldItsaMe", 36);
	playerHud->AddComponent(std::move(hudText));

	std::unique_ptr<CHUDElement> hudCHud = std::make_unique<CHUDElement>(playerHud.get(), m_pPlayerOnePawn.get());
	playerHud->AddComponent(std::move(hudCHud));

	const auto hudTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> hudRender = std::make_unique<CRender>(playerHud.get(), hudTexture, false);
	playerHud->AddComponent(std::move(hudRender));

	scene->Add(playerHud);
#pragma region UI

#pragma endregion UI

#pragma region NPC
	const auto npc = std::make_shared<GameObject>("blueTank0");
	npc->GetTransform()->SetPosition(350, 150);
	npc->GetTransform()->SetScale(44, 44);

	const auto blueTankTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankBlue.png");
	std::unique_ptr<CRender> npcCRender = std::make_unique<CRender>(npc.get(), blueTankTexture, true);
	npc->AddComponent(std::move(npcCRender));

	std::unique_ptr<CCollisionBox> npcCCollision = std::make_unique<CCollisionBox>(npc.get(), CollisionGroup::NPC);
	npc->AddComponent(std::move(npcCCollision));

	std::unique_ptr<CHealth> npcCHealth = std::make_unique<CHealth>(npc.get());
	npc->AddComponent(std::move(npcCHealth));

	std::unique_ptr<CTankNPC> npcCTankNPC = std::make_unique<CTankNPC>(npc.get(), TankType::BlueTank);
	npc->AddComponent(std::move(npcCTankNPC));

	scene->Add(npc);
#pragma endregion NPC

#pragma region GameplayObjects
	const auto diamond = std::make_shared<GameObject>(std::string{ "Diamond" });
	diamond->GetTransform()->SetPosition(225, 300);
	diamond->GetTransform()->SetScale(60, 60);

	const auto diamondTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> diamondCRender = std::make_unique<CRender>(diamond.get(), diamondTexture, true);
	diamond->AddComponent(std::move(diamondCRender));

	std::unique_ptr<CCollisionBox> diamondCCollision = std::make_unique<CCollisionBox>(diamond.get(), CollisionGroup::Diamond);
	diamond->AddComponent(std::move(diamondCCollision));

	std::unique_ptr<CDiamond> diamondCDiamond = std::make_unique<CDiamond>(diamond.get());
	diamond->AddComponent(std::move(diamondCDiamond));

	scene->Add(diamond);
#pragma endregion GameplayObjects

#pragma region Terrain
	const auto wallTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//0//
	const auto wall = std::make_shared<GameObject>(std::string{ "Wall00" });
	//CTRANSFORM
	wall->GetTransform()->SetPosition(100, 100);
	wall->GetTransform()->SetScale(300, 30);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender = std::make_unique<CRender>(wall.get(), wallTexture, true);
	wall->AddComponent(std::move(wallCRender));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision = std::make_unique<CCollisionBox>(wall.get(), CollisionGroup::Wall);
	wall->AddComponent(std::move(wallCCollision));
	scene->Add(wall);
	//1//
	const auto wall2 = std::make_shared<GameObject>(std::string{ "Wall01" });
	//CTRANSFORM
	wall2->GetTransform()->SetPosition(400, 100);
	wall2->GetTransform()->SetScale(30, 300);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender2 = std::make_unique<CRender>(wall2.get(), wallTexture, true);
	wall2->AddComponent(std::move(wallCRender2));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision2 = std::make_unique<CCollisionBox>(wall2.get(), CollisionGroup::Wall);
	wall2->AddComponent(std::move(wallCCollision2));
	scene->Add(wall2);
	//2//
	const auto wall3 = std::make_shared<GameObject>(std::string{ "Wall02" });
	//CTRANSFORM
	wall3->GetTransform()->SetPosition(100, 400);
	wall3->GetTransform()->SetScale(300, 30);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender3 = std::make_unique<CRender>(wall3.get(), wallTexture, true);
	wall3->AddComponent(std::move(wallCRender3));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision3 = std::make_unique<CCollisionBox>(wall3.get(), CollisionGroup::Wall);
	wall3->AddComponent(std::move(wallCCollision3));
	scene->Add(wall3);
	//3//
	const auto wall4 = std::make_shared<GameObject>(std::string{ "Wall03" });
	//CTRANSFORM
	wall4->GetTransform()->SetPosition(100, 100);
	wall4->GetTransform()->SetScale(30, 300);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender4 = std::make_unique<CRender>(wall4.get(), wallTexture, true);
	wall4->AddComponent(std::move(wallCRender4));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision4 = std::make_unique<CCollisionBox>(wall4.get(), CollisionGroup::Wall);
	wall4->AddComponent(std::move(wallCCollision4));
	scene->Add(wall4);
#pragma endregion Terrain
}

void Tron::CreateScene1()
{
	auto scene = SceneManager::GetInstance().GetScene(1);

#pragma region PlayerPawns
	if (m_pPlayerOnePawn)
	{
		scene->Add(m_pPlayerOnePawn);
		m_pPlayerOnePawn->GetTransform()->SetPosition(350, 150);
		scene->Add(m_pPlayerOnePawn->GetChildren()[0]);
	}
#pragma endregion PlayerPawns
}

void Tron::CreateScene2()
{
	auto scene = SceneManager::GetInstance().GetScene(2);

#pragma region PlayerPawns
	if (m_pPlayerOnePawn)
	{
		scene->Add(m_pPlayerOnePawn);
		m_pPlayerOnePawn->GetTransform()->SetPosition(150, 350);
		scene->Add(m_pPlayerOnePawn->GetChildren()[0]);
	}
#pragma endregion PlayerPawns
}

InputManager* Tron::ConfigureInput()
{
	InputManager* inputManager = new InputManager{};

	//INPUT PAWN ONE
	// GAMEPAD
	inputManager->BindCommandToButton(ControllerButton::DPadRight, std::make_unique<MoveHorizontal>(true));
	inputManager->BindCommandToButton(ControllerButton::DPadLeft, std::make_unique<MoveHorizontal>(false));
	inputManager->BindCommandToButton(ControllerButton::DPadUp, std::make_unique<MoveVertical>(true));
	inputManager->BindCommandToButton(ControllerButton::DPadDown, std::make_unique<MoveVertical>(false));
	inputManager->AddController(0, m_pPlayerOnePawn.get());
	//KEYBOARD|MOUSE
	inputManager->BindCommandToButton(SDL_SCANCODE_D, std::make_unique<MoveHorizontal>(true));
	inputManager->BindCommandToButton(SDL_SCANCODE_A, std::make_unique<MoveHorizontal>(false));
	inputManager->BindCommandToButton(SDL_SCANCODE_W, std::make_unique<MoveVertical>(true));
	inputManager->BindCommandToButton(SDL_SCANCODE_S, std::make_unique<MoveVertical>(false));
	inputManager->BindCommandToButton(SDL_SCANCODE_KP_0, std::make_unique<OpenScene>(0));
	inputManager->BindCommandToButton(SDL_SCANCODE_0, std::make_unique<OpenScene>(0));
	inputManager->BindCommandToButton(SDL_SCANCODE_KP_1, std::make_unique<OpenScene>(1));
	inputManager->BindCommandToButton(SDL_SCANCODE_1, std::make_unique<OpenScene>(1));
	inputManager->BindCommandToButton(SDL_SCANCODE_KP_2, std::make_unique<OpenScene>(2));
	inputManager->BindCommandToButton(SDL_SCANCODE_2, std::make_unique<OpenScene>(2));
	inputManager->BindCommandToButton(SDL_SCANCODE_R, std::make_unique<ResetScene>());
	inputManager->BindCommandToButton(SDL_BUTTON_LMASK, std::make_unique<Shoot>(), true);
	inputManager->AddController(4, m_pPlayerOnePawn.get());

	return inputManager;
}

void Tron::PrintStartMessage()
{
	std::cout << "Level 0\t:\tPress '0'\n";
	std::cout << "Level 1\t:\tPress '1'\n";
	std::cout << "Level 2\t:\tPress '2'\n";
}