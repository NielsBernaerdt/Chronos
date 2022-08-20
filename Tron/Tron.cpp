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

//json
#include <rapidjson/rapidjson.h>
#include <rapidjson/document.h>
#include <rapidjson/stream.h>
#include <rapidjson/filereadstream.h>

std::shared_ptr<GameObject> Tron::m_pPlayerOnePawn = nullptr;
std::shared_ptr<GameObject> Tron::m_pPlayerTwoPawn = nullptr;
int Tron::m_NrEnemies{ 2 };

bool Tron::ReadFromFile()
{
	//READ FILE, RETURN TRUE IF INVALID
	rapidjson::Document jsonDoc{};
	if (ParseJSON("../Data/GameConfiguration.json", jsonDoc))
	{
		using rapidjson::Value;
		m_GameMode = jsonDoc["GameMode"].GetString();
		if (m_GameMode == "Versus")
			m_NrEnemies = 0;
		else
			m_NrEnemies = jsonDoc["NrEnemies"].GetInt();
		if (m_GameMode != "Singleplayer" && m_GameMode != "SinglePlayer"
			&& m_GameMode != "Versus"
			&& m_GameMode != "Coop")
		{
			std::cout << "WRONG GAMEMODE\n";
			return true;
		}
		if (m_NrEnemies < 0 || m_NrEnemies >= 7)
		{
			std::cout << "INVALID NUMBER OF ENEMIES\n";
			return true;
		}
	}
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

bool Tron::ParseJSON(const char* fileName, rapidjson::Document& jsonDoc)
{
	FILE* fp = nullptr;
	fopen_s(&fp, fileName, "rb");

	if (fp != nullptr)
	{
		fseek(fp, 0, SEEK_END);
		size_t size = ftell(fp);
		fseek(fp, 0, SEEK_SET);
		char* readBuffer = new char[size];
		rapidjson::FileReadStream is(fp, readBuffer, sizeof(readBuffer));
		jsonDoc.ParseStream(is);
		delete[] readBuffer;
		fclose(fp);
		return true;
	}
	return false;
}

void Tron::CreatePawns()
{
#pragma region PlayerPawnOne
	{
		const auto tronTank = std::make_shared<GameObject>(std::string{ "TronPawnOne" });
		tronTank->GetTransform()->SetPosition(150, 150);
		tronTank->GetTransform()->SetScale(38, 38);

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
		tronTankBarrel->GetTransform()->SetPosition(-11, 13);
		tronTankBarrel->GetTransform()->SetScale(60, 20);

		const auto tronBarrelTexture = ResourceManager::GetInstance().LoadTexture("../Data/Tron/TankBarrel.png");
		std::unique_ptr<CRender> tronBarrelCRender = std::make_unique<CRender>(tronTankBarrel.get(), tronBarrelTexture, true);
		tronTankBarrel->AddComponent(std::move(tronBarrelCRender));

		tronTankBarrel->SetParent(m_pPlayerOnePawn.get(), tronTankBarrel);
	}
#pragma endregion PlayerPawnOne

#pragma region PlayerPawnTwoCoop
	if (m_GameMode == "Coop")
	{
		const auto tronTwoTank = std::make_shared<GameObject>(std::string{ "TronPawnTwo" });
		tronTwoTank->GetTransform()->SetPosition(150, 150);
		tronTwoTank->GetTransform()->SetScale(38, 38);

		const auto tronTwoTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankGreen.png");
		std::unique_ptr<CRender> tronCRender = std::make_unique<CRender>(tronTwoTank.get(), tronTwoTexture, true);
		tronTwoTank->AddComponent(std::move(tronCRender));

		std::unique_ptr<CTankTron> tronCTankTron = std::make_unique<CTankTron>(tronTwoTank.get());
		tronTwoTank->AddComponent(std::move(tronCTankTron));

		std::unique_ptr<CCollisionBox> tronCCollision = std::make_unique<CCollisionBox>(tronTwoTank.get(), CollisionGroup::Pawn);
		tronTwoTank->AddComponent(std::move(tronCCollision));

		std::unique_ptr<CPoints> tronCPoints = std::make_unique<CPoints>(tronTwoTank.get());
		tronCPoints->SetPoints(300);
		tronTwoTank->AddComponent(std::move(tronCPoints));

		std::unique_ptr<CHealth> tronCHealth = std::make_unique<CHealth>(tronTwoTank.get(), 3);
		tronTwoTank->AddComponent(std::move(tronCHealth));

		m_pPlayerTwoPawn = tronTwoTank;

		/////////////////TANKBARREL////////////////////
		const auto tronTwoTankBarrel = std::make_shared<GameObject>(std::string{ "TronPawnTwoBarrel" });
		tronTwoTankBarrel->GetTransform()->SetPosition(-11, 13);
		tronTwoTankBarrel->GetTransform()->SetScale(60, 20);

		const auto tronBarrelTexture = ResourceManager::GetInstance().LoadTexture("../Data/Tron/TankBarrel.png");
		std::unique_ptr<CRender> tronBarrelCRender = std::make_unique<CRender>(tronTwoTankBarrel.get(), tronBarrelTexture, true);
		tronTwoTankBarrel->AddComponent(std::move(tronBarrelCRender));

		tronTwoTankBarrel->SetParent(m_pPlayerTwoPawn.get(), tronTwoTankBarrel);
	}
#pragma region PlayerPawnTwoCoop

#pragma region PlayerPawnTwoVersus
	if (m_GameMode == "Versus")
	{
		const auto tronTwoTank = std::make_shared<GameObject>(std::string{ "TronPawnTwo" });
		tronTwoTank->GetTransform()->SetPosition(150, 150);
		tronTwoTank->GetTransform()->SetScale(38, 38);

		const auto tronTwoTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankGreen.png");
		std::unique_ptr<CRender> tronCRender = std::make_unique<CRender>(tronTwoTank.get(), tronTwoTexture, true);
		tronTwoTank->AddComponent(std::move(tronCRender));

		std::unique_ptr<CTankTron> tronCTankTron = std::make_unique<CTankTron>(tronTwoTank.get());
		tronTwoTank->AddComponent(std::move(tronCTankTron));

		std::unique_ptr<CCollisionBox> tronCCollision = std::make_unique<CCollisionBox>(tronTwoTank.get(), CollisionGroup::NPC);
		tronTwoTank->AddComponent(std::move(tronCCollision));

		std::unique_ptr<CPoints> tronCPoints = std::make_unique<CPoints>(tronTwoTank.get());
		tronCPoints->SetPoints(300);
		tronTwoTank->AddComponent(std::move(tronCPoints));

		std::unique_ptr<CHealth> tronCHealth = std::make_unique<CHealth>(tronTwoTank.get(), 3);
		tronTwoTank->AddComponent(std::move(tronCHealth));

		m_pPlayerTwoPawn = tronTwoTank;

		/////////////////TANKBARREL////////////////////
		const auto tronTwoTankBarrel = std::make_shared<GameObject>(std::string{ "TronPawnTwoBarrel" });
		tronTwoTankBarrel->GetTransform()->SetPosition(-11, 13);
		tronTwoTankBarrel->GetTransform()->SetScale(60, 20);

		const auto tronBarrelTexture = ResourceManager::GetInstance().LoadTexture("../Data/Tron/TankBarrel.png");
		std::unique_ptr<CRender> tronBarrelCRender = std::make_unique<CRender>(tronTwoTankBarrel.get(), tronBarrelTexture, true);
		tronTwoTankBarrel->AddComponent(std::move(tronBarrelCRender));

		tronTwoTankBarrel->SetParent(m_pPlayerTwoPawn.get(), tronTwoTankBarrel);
	}
#pragma region PlayerPawnTwoVersus

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
		m_pPlayerOnePawn->GetTransform()->SetPosition(23, 65);
		scene->Add(m_pPlayerOnePawn->GetChildren()[0]);
	}
	if (m_pPlayerTwoPawn)
	{
		scene->Add(m_pPlayerTwoPawn);
		m_pPlayerTwoPawn->GetTransform()->SetPosition(420, 65);
		scene->Add(m_pPlayerTwoPawn->GetChildren()[0]);
	}
//HUD//
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
#pragma endregion PlayerPawns

	using rapidjson::Value;
	rapidjson::Document jsonDoc{};
	
	if (ParseJSON("../Data/level0.json", jsonDoc))
	{

#pragma region Gameplay Objects

		if (jsonDoc.HasMember("diamond"))
		{
			const Value& diamondAttributes = jsonDoc["diamond"];

			std::string wallName = diamondAttributes["Name"].GetString();
			int wallPosX = diamondAttributes["PosX"].GetInt();
			int wallPosY = diamondAttributes["PosY"].GetInt();
			int wallScaleX = diamondAttributes["ScaleX"].GetInt();
			int wallScaleY = diamondAttributes["ScaleY"].GetInt();

			const auto diamond = std::make_shared<GameObject>(wallName);
			diamond->GetTransform()->SetPosition(wallPosX, wallPosY);
			diamond->GetTransform()->SetScale(wallScaleX, wallScaleY);

			const auto diamondTexture = ResourceManager::GetInstance().LoadTexture("../Data/Tron/Diamond.png");
			std::unique_ptr<CRender> diamondCRender = std::make_unique<CRender>(diamond.get(), diamondTexture, true);
			diamond->AddComponent(std::move(diamondCRender));

			std::unique_ptr<CCollisionBox> diamondCCollision = std::make_unique<CCollisionBox>(diamond.get(), CollisionGroup::Diamond);
			diamond->AddComponent(std::move(diamondCCollision));

			std::unique_ptr<CDiamond> diamondCDiamond = std::make_unique<CDiamond>(diamond.get());
			diamond->AddComponent(std::move(diamondCDiamond));

			scene->Add(diamond);
		}

#pragma endregion Gameplay Objects

#pragma region Walls
		if (jsonDoc.HasMember("walls"))
		{
			const auto wallTexture = ResourceManager::GetInstance().LoadTexture("../Data/Tron/WallGreen.png");
			const Value& wallArray = jsonDoc["walls"];
			for (rapidjson::SizeType i = 0; i < wallArray.Size(); ++i)
			{
				if (wallArray[i].IsObject())
				{
					std::string wallName = wallArray[i]["Name"].GetString();
					int wallPosX = wallArray[i]["PosX"].GetInt();
					int wallPosY = wallArray[i]["PosY"].GetInt();
					int wallScaleX = wallArray[i]["ScaleX"].GetInt();
					int wallScaleY = wallArray[i]["ScaleY"].GetInt();

					const auto wall = std::make_shared<GameObject>(wallName);
					//CTRANSFORM
					wall->GetTransform()->SetPosition(wallPosX, wallPosY);
					wall->GetTransform()->SetScale(wallScaleX,wallScaleY);
					//TEX + CRENDER
					std::unique_ptr<CRender> wallCRender = std::make_unique<CRender>(wall.get(), wallTexture, true);
					wall->AddComponent(std::move(wallCRender));
					//CCOLLISION
					std::unique_ptr<CCollisionBox> wallCCollision = std::make_unique<CCollisionBox>(wall.get(), CollisionGroup::Wall);
					wall->AddComponent(std::move(wallCCollision));
					scene->Add(wall);
				}
			}
		}
#pragma endregion Walls

#pragma region Enemies
		if (jsonDoc.HasMember("enemies"))
		{
			const auto blueTankTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankBlue.png");
			const Value& enemyArray = jsonDoc["enemies"];
			for (rapidjson::SizeType i = 0; i < static_cast<rapidjson::SizeType>(m_NrEnemies); ++i)
			{
				if (enemyArray[i].IsObject())
				{
					std::string enemyName = enemyArray[i]["Name"].GetString();
					int enemyPosX = enemyArray[i]["PosX"].GetInt();
					int enemyPosY = enemyArray[i]["PosY"].GetInt();

					const auto npc = std::make_shared<GameObject>(enemyName);
					npc->GetTransform()->SetPosition(enemyPosX, enemyPosY);
					npc->GetTransform()->SetScale(38, 38);

					std::unique_ptr<CRender> npcCRender = std::make_unique<CRender>(npc.get(), blueTankTexture, true);
					npc->AddComponent(std::move(npcCRender));

					std::unique_ptr<CCollisionBox> npcCCollision = std::make_unique<CCollisionBox>(npc.get(), CollisionGroup::NPC);
					npc->AddComponent(std::move(npcCCollision));

					std::unique_ptr<CHealth> npcCHealth = std::make_unique<CHealth>(npc.get());
					npc->AddComponent(std::move(npcCHealth));

					std::unique_ptr<CTankNPC> npcCTankNPC = std::make_unique<CTankNPC>(npc.get(), TankType::BlueTank);
					npc->AddComponent(std::move(npcCTankNPC));

					scene->Add(npc);
				}
			}
		}
#pragma endregion Enemies
	}
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

	if (m_GameMode == "Singleplayer" || m_GameMode == "SinglePlayer")
	{
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
	}
	if (m_GameMode == "Coop" || m_GameMode == "Versus")
	{
		//INPUT PAWN ONE
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
		//INPUT PAWN TWO
		//GAMEPAD
		inputManager->BindCommandToButton(ControllerButton::DPadRight, std::make_unique<MoveHorizontal>(true));
		inputManager->BindCommandToButton(ControllerButton::DPadLeft, std::make_unique<MoveHorizontal>(false));
		inputManager->BindCommandToButton(ControllerButton::DPadUp, std::make_unique<MoveVertical>(true));
		inputManager->BindCommandToButton(ControllerButton::DPadDown, std::make_unique<MoveVertical>(false));
		inputManager->BindCommandToButton(ControllerButton::ButtonX, std::make_unique<Shoot>());
		inputManager->AddController(0, m_pPlayerTwoPawn.get());
	}
	return inputManager;
}

void Tron::PrintStartMessage()
{
	std::cout << "Level 0\t:\tPress '0'\n";
	std::cout << "Level 1\t:\tPress '1'\n";
	std::cout << "Level 2\t:\tPress '2'\n";
}