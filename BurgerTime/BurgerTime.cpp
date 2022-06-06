#include "BurgerTime.h"
#include <iostream>
#include <fstream>
#include "CollisionGroups.h"
#include "InputManager.h"
#include "InputCommands.h"
#include "ResourceManager.h"
#include "Scene.h"
//components
#include "CFPS.h"
#include "CHealth.h"
#include "CRender.h"
#include "CText.h"
#include "CBurgerIngredient.h"
#include "CCollisionBox.h"
#include "CEnemyPlayer.h"
#include "CMrHotDog.h"
#include "CPeterPepper.h"
#include "CPlate.h"
#include "CPoints.h"
//Observers
#include "CHUDElement.h"
#include "GameState.h"

bool BurgerTime::ReadFromFile()
{
	std::fstream newfile;
	newfile.open("../Data/LevelLayout.txt", std::ios::in);
	if (newfile.is_open()) {
		std::string tp;

		std::getline(newfile, tp, '\n'); //First line "Level:"
		std::getline(newfile, tp, '\n'); //Second line "1"
		m_Map = std::stoi(tp);
		std::getline(newfile, tp, '\n'); //Third line "GameMode:" 
		std::getline(newfile, tp, '\n'); //Fourth line "SinglePlayer"
		m_GameMode = tp;
		std::getline(newfile, tp, '\n'); //Fifth line "Nr Enemies:"
		std::getline(newfile, tp, '\n'); //Sixth line "5"
		m_NrEnemies = std::stoi(tp);
		std::getline(newfile, tp, '\n'); //Seventh line "Nr BurgerIngredients:"
		std::getline(newfile, tp, '\n'); //Eight line "8"
		m_NrBurgerIngredients = std::stoi(tp);

		newfile.close();
	}
	if(m_Map < 0 || m_Map >= 3)
	{
		std::cout << "WRONG LEVEL MAP INDEX\n";
		return true;
	}
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
	if(m_NrBurgerIngredients !=3
		&& m_NrBurgerIngredients != 6
		&& m_NrBurgerIngredients != 10
		&& m_NrBurgerIngredients != 14)
	{
		std::cout << "INVALID NUMBER OF BURGER INGREDIENTS\n";
		return true;
	}
	return false;
}

void BurgerTime::DetermineObjectsLocations()
{
	//BURGERS//
	//burger 01
	m_BurgerLocations.push_back(glm::vec3{48, 130, 0});
	m_BurgerIngredients.push_back(Ingredient::Patty);
	//burger 02
	m_BurgerLocations.push_back(glm::vec3{48, 50, 0});
	m_BurgerIngredients.push_back(Ingredient::BunTop);
	//burger 03
	m_BurgerLocations.push_back(glm::vec3{48, 200, 0});
	m_BurgerIngredients.push_back(Ingredient::BunBottom);
	//burger 04
	m_BurgerLocations.push_back(glm::vec3{ 478, 180, 0 });
	m_BurgerIngredients.push_back(Ingredient::Cheese);
	//burger 05
	m_BurgerLocations.push_back(glm::vec3{ 478, 50, 0 });
	m_BurgerIngredients.push_back(Ingredient::BunTop);
	//burger 06
	m_BurgerLocations.push_back(glm::vec3{ 478, 230, 0 });
	m_BurgerIngredients.push_back(Ingredient::BunBottom);
	//burger 07
	m_BurgerLocations.push_back(glm::vec3{ 185, 60, 0 });
	m_BurgerIngredients.push_back(Ingredient::Tomato);
	//burger 08
	m_BurgerLocations.push_back(glm::vec3{ 185, 20, 0 });
	m_BurgerIngredients.push_back(Ingredient::BunTop);
	//burger 09
	m_BurgerLocations.push_back(glm::vec3{ 185, 280, 0 });
	m_BurgerIngredients.push_back(Ingredient::Lettuce);
	//burger 10
	m_BurgerLocations.push_back(glm::vec3{ 185, 400, 0 });
	m_BurgerIngredients.push_back(Ingredient::BunBottom);
	//burger 11
	m_BurgerLocations.push_back(glm::vec3{ 325, 170, 0 });
	m_BurgerIngredients.push_back(Ingredient::Patty);
	//burger 12
	m_BurgerLocations.push_back(glm::vec3{ 325, 50, 0 });
	m_BurgerIngredients.push_back(Ingredient::BunTop);
	//burger 13
	m_BurgerLocations.push_back(glm::vec3{ 325, 280, 0 });
	m_BurgerIngredients.push_back(Ingredient::Lettuce);
	//burger 14
	m_BurgerLocations.push_back(glm::vec3{ 325, 380, 0 });
	m_BurgerIngredients.push_back(Ingredient::BunBottom);

	//NPCs//
	//npc 01
	m_NPCLocations.push_back(glm::vec3{40, 200, 0});
	//npc 02
	m_NPCLocations.push_back(glm::vec3{400, 200, 0});
	//npc 03
	m_NPCLocations.push_back(glm::vec3{225, 300, 0});
	//npc 04
	m_NPCLocations.push_back(glm::vec3{500, 100, 0});
	//npc 05
	m_NPCLocations.push_back(glm::vec3{50, 200, 0});
	//npc 06
	m_NPCLocations.push_back(glm::vec3{50, 400, 0});
}


void BurgerTime::CreateLevel(Scene& scene)
{
	//OBSERVERS
	auto observer = std::make_shared<GameState>(nullptr);

	std::string mapName{"level"};
	mapName += std::to_string(m_Map) + ".png";
	//Background image
	std::shared_ptr<GameObject> background = std::make_shared<GameObject>(std::string{ "Background" });
	background->GetTransform()->SetScale(620, 620);
	auto bgTexture = ResourceManager::GetInstance().LoadTexture(mapName);
	std::unique_ptr<CRender> bgCRender = std::make_unique<CRender>(background.get(), bgTexture, true);
	background->AddComponent(std::move(bgCRender));
	scene.Add(background);

	//Make FPS object
	const auto fpsCounter = std::make_shared<GameObject>(std::string{ "FPSCounter" });
	std::unique_ptr<CText> fpsCText = std::make_unique<CText>(fpsCounter.get(), "FPS Counter", 36);
	fpsCounter->AddComponent(std::move(fpsCText));
	std::unique_ptr<CFPS> fpsComp = std::make_unique<CFPS>(fpsCounter.get());
	fpsCounter->AddComponent(std::move(fpsComp));
	auto fpsTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> fpsCRender = std::make_unique<CRender>(fpsCounter.get(), fpsTexture, false);
	fpsCounter->AddComponent(std::move(fpsCRender));
	scene.Add(fpsCounter);

	CreatePlayerPawns(scene, observer);
	if(m_GameMode != "Versus") CreateNPCs(scene, observer);
	switch(m_Map)
	{
	case 0:
		CreateTerrainLevel0(scene);
		break;
	case 1:
		CreateTerrainLevel1(scene);
		break;
	case 2:
		CreateTerrainLevel2(scene);
	}
	CreateGameplayObjects(scene, observer);
}

void BurgerTime::CreatePlayerPawns(Scene& scene, std::shared_ptr<GameState> pObserver)
{
	//PAWN ONE
	const auto peterPepper = std::make_shared<GameObject>(std::string{ "Peter" });
	peterPepper->GetTransform()->SetPosition(0, 90);
	peterPepper->GetTransform()->SetScale(44, 44);
	std::unique_ptr<CCollisionBox> peterCollision = std::make_unique<CCollisionBox>(peterPepper.get(), CollisionGroup::Pawn);
	peterPepper->AddComponent(std::move(peterCollision));
	const auto peterTexture = ResourceManager::GetInstance().LoadTexture("PeterSprites.png");
	std::unique_ptr<CRender> peterCRender = std::make_unique<CRender>(peterPepper.get(), peterTexture, true);
	peterPepper->AddComponent(std::move(peterCRender));
	std::unique_ptr<CPeterPepper> peterCPeterPepper = std::make_unique<CPeterPepper>(peterPepper.get());
	peterPepper->AddComponent(std::move(peterCPeterPepper));
	std::unique_ptr<CHealth> peterCHealth = std::make_unique<CHealth>(peterPepper.get(), 3);
	peterPepper->AddComponent(std::move(peterCHealth));
	std::unique_ptr<CPoints> peterCPoints = std::make_unique<CPoints>(peterPepper.get());
	peterPepper->AddComponent(std::move(peterCPoints));
	peterPepper->AddObserver(pObserver);
	scene.Add(peterPepper);
	m_pPlayerOnePawn = peterPepper.get();
	pObserver->SetPawn(peterPepper.get());
	//HUD PAWN ONE
	const auto playerHud = std::make_shared<GameObject>(std::string{ "playerHud" });
	playerHud->GetTransform()->SetPosition(200, 0);
	const auto hudTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CText> hudText = std::make_unique<CText>(playerHud.get(), "HelloWorldItsaMe", 36);
	playerHud->AddComponent(std::move(hudText));
	std::unique_ptr<CHUDElement> hudCHud = std::make_unique<CHUDElement>(playerHud.get(), peterPepper.get());
	playerHud->AddComponent(std::move(hudCHud));
	std::unique_ptr<CRender> hudRender = std::make_unique<CRender>(playerHud.get(), hudTexture, false);
	playerHud->AddComponent(std::move(hudRender));
	scene.Add(playerHud);

	if (m_GameMode == "Coop")
	{
		const auto peterPepper2 = std::make_shared<GameObject>(std::string{ "Peter" });
		peterPepper2->GetTransform()->SetPosition(0, 90);
		peterPepper2->GetTransform()->SetScale(44, 44);
		std::unique_ptr<CCollisionBox> peterCollision2 = std::make_unique<CCollisionBox>(peterPepper2.get(), CollisionGroup::Pawn);
		peterPepper2->AddComponent(std::move(peterCollision2));
		const auto peterTexture2 = ResourceManager::GetInstance().LoadTexture("PeterSprites.png");
		std::unique_ptr<CRender> peterCRender2 = std::make_unique<CRender>(peterPepper2.get(), peterTexture2, true);
		peterPepper2->AddComponent(std::move(peterCRender2));
		std::unique_ptr<CPeterPepper> peterCPeterPepper2 = std::make_unique<CPeterPepper>(peterPepper2.get());
		peterPepper2->AddComponent(std::move(peterCPeterPepper2));
		std::unique_ptr<CHealth> peterCHealth2 = std::make_unique<CHealth>(peterPepper2.get(), 3);
		peterPepper2->AddComponent(std::move(peterCHealth2));
		peterPepper2->AddObserver(pObserver);
		scene.Add(peterPepper2);
		m_pPlayerTwoPawn = peterPepper2.get();
	}
	else if (m_GameMode == "Versus")
	{
		const auto peterPepper2 = std::make_shared<GameObject>(std::string{ "Peter" });
		peterPepper2->GetTransform()->SetPosition(590, 35);
		peterPepper2->GetTransform()->SetScale(44, 44);
		std::unique_ptr<CCollisionBox> peterCollision2 = std::make_unique<CCollisionBox>(peterPepper2.get(), CollisionGroup::NPC);
		peterPepper2->AddComponent(std::move(peterCollision2));
		const auto hotDogTexture = ResourceManager::GetInstance().LoadTexture("HotDogSprites.png");
		std::unique_ptr<CRender> peterCRender2 = std::make_unique<CRender>(peterPepper2.get(), hotDogTexture, true);
		peterPepper2->AddComponent(std::move(peterCRender2));
		std::unique_ptr<CEnemyPlayer> peterCPeterPepper2 = std::make_unique<CEnemyPlayer>(peterPepper2.get());
		peterPepper2->AddComponent(std::move(peterCPeterPepper2));
		std::unique_ptr<CHealth> peterCHealth2 = std::make_unique<CHealth>(peterPepper2.get(), 3);
		peterPepper2->AddComponent(std::move(peterCHealth2));
		peterPepper2->AddObserver(pObserver);
		scene.Add(peterPepper2);
		m_pPlayerTwoPawn = peterPepper2.get();
	}
}

void BurgerTime::CreateNPCs(Scene& scene, std::shared_ptr<GameState> pObserver)
{
	//COMMON RESOURCES//
	const auto hotDogTexture = ResourceManager::GetInstance().LoadTexture("HotDogSprites.png");
	//
	for (int parentIndex{}; parentIndex < m_NrEnemies; ++parentIndex)
	{
		const auto mrHotDog = std::make_shared<GameObject>(std::string{ "MrHotDog" });
		mrHotDog->GetTransform()->SetPosition(m_NPCLocations[parentIndex]);
		mrHotDog->GetTransform()->SetScale(44, 44);
		std::unique_ptr<CCollisionBox> hotdogCollision = std::make_unique<CCollisionBox>(mrHotDog.get(), CollisionGroup::NPC);
		mrHotDog->AddComponent(std::move(hotdogCollision));
		std::unique_ptr<CRender> hotDogCRender = std::make_unique<CRender>(mrHotDog.get(), hotDogTexture, true);
		mrHotDog->AddComponent(std::move(hotDogCRender));
		std::unique_ptr<CMrHotDog> hotDogCHotDog = std::make_unique<CMrHotDog>(mrHotDog.get());
		mrHotDog->AddComponent(std::move(hotDogCHotDog));
		std::unique_ptr<CHealth> hotDogCHealth = std::make_unique<CHealth>(mrHotDog.get(), 1);
		mrHotDog->AddComponent(std::move(hotDogCHealth));
		mrHotDog->AddObserver(pObserver);
		scene.Add(mrHotDog);
	}
}

void BurgerTime::CreateGameplayObjects(Scene& scene, std::shared_ptr<GameState>)
{
	//COMMON RESOURCES
	const auto pattyTexture = ResourceManager::GetInstance().LoadTexture("BurgerIngredients.png");
	constexpr size_t nrBurgerParts{ 4 };
	int scale{ 24 };

	for(int parentIndex{}; parentIndex < m_NrBurgerIngredients; ++parentIndex)
	{
		const auto burger = std::make_shared<GameObject>(std::string{ "burger" + std::to_string(parentIndex) });
		burger->GetTransform()->SetPosition(m_BurgerLocations[parentIndex]);
		std::unique_ptr<CBurgerIngredient> burgerCBurgerIngredient = std::make_unique<CBurgerIngredient>(burger.get(), m_BurgerIngredients[parentIndex]);
		burger->AddComponent(std::move(burgerCBurgerIngredient));
		for (size_t childIndex{}; childIndex < nrBurgerParts; ++childIndex)
		{
			const auto child = std::make_shared<GameObject>(std::string{ "PattyChild0" + std::to_string(childIndex) });
			child->GetTransform()->SetPosition((int)childIndex * scale, 0);
			child->GetTransform()->SetScale(scale, scale);
			std::unique_ptr<CCollisionBox> pattyChildCollision = std::make_unique<CCollisionBox>(child.get(), CollisionGroup::Burger);
			child->AddComponent(std::move(pattyChildCollision));
			std::unique_ptr<CRender> pattychildCRender = std::make_unique<CRender>(child.get(), pattyTexture, true);
			child->AddComponent(std::move(pattychildCRender));
			child->SetParent(burger.get());
			scene.Add(child);
		}
		scene.Add(burger);
	}

	//BURGER PLATES AT BOTTOM
	//COMMON RESOURCES
	const auto plateTexture = ResourceManager::GetInstance().LoadEmptyTexture();

	if (m_Map == 0)
	{
		//0//
		const auto plate = std::make_shared<GameObject>(std::string{ "plate" });
		plate->GetTransform()->SetPosition(35, 475);
		plate->GetTransform()->SetScale(160, 5);
		//std::unique_ptr<CRender> plateCRender = std::make_unique<CRender>(plate.get(), plateTexture);
		//plate->AddComponent(std::move(plateCRender));
		std::unique_ptr<CCollisionBox> plateCCollision = std::make_unique<CCollisionBox>(plate.get(), CollisionGroup::Plate);
		plate->AddComponent(std::move(plateCCollision));
		std::unique_ptr<CPlate> plateCPlate = std::make_unique<CPlate>(plate.get(), true);
		plate->AddComponent(std::move(plateCPlate));
		scene.Add(plate);
		//1//
		const auto plate1 = std::make_shared<GameObject>(std::string{ "plate" });
		plate1->GetTransform()->SetPosition(475, 475);
		plate1->GetTransform()->SetScale(160, 5);
		//std::unique_ptr<CRender> plateCRender1 = std::make_unique<CRender>(plate1.get(), plateTexture);
		//plate1->AddComponent(std::move(plateCRender1));
		std::unique_ptr<CCollisionBox> plateCCollision1 = std::make_unique<CCollisionBox>(plate1.get(), CollisionGroup::Plate);
		plate1->AddComponent(std::move(plateCCollision1));
		std::unique_ptr<CPlate> plateCPlate1 = std::make_unique<CPlate>(plate1.get(), true);
		plate1->AddComponent(std::move(plateCPlate1));
		scene.Add(plate1);
	}
	else
	{
		//0//
		const auto plate = std::make_shared<GameObject>(std::string{ "plate" });
		plate->GetTransform()->SetPosition(35, 615);
		plate->GetTransform()->SetScale(160, 5);
		//std::unique_ptr<CRender> plateCRender = std::make_unique<CRender>(plate.get(), plateTexture);
		//plate->AddComponent(std::move(plateCRender));
		std::unique_ptr<CCollisionBox> plateCCollision = std::make_unique<CCollisionBox>(plate.get(), CollisionGroup::Plate);
		plate->AddComponent(std::move(plateCCollision));
		std::unique_ptr<CPlate> plateCPlate = std::make_unique<CPlate>(plate.get(), true);
		plate->AddComponent(std::move(plateCPlate));
		scene.Add(plate);
		//1//
		const auto plate1 = std::make_shared<GameObject>(std::string{ "plate" });
		plate1->GetTransform()->SetPosition(475, 615);
		plate1->GetTransform()->SetScale(160, 5);
		//std::unique_ptr<CRender> plateCRender1 = std::make_unique<CRender>(plate1.get(), plateTexture);
		//plate1->AddComponent(std::move(plateCRender1));
		std::unique_ptr<CCollisionBox> plateCCollision1 = std::make_unique<CCollisionBox>(plate1.get(), CollisionGroup::Plate);
		plate1->AddComponent(std::move(plateCCollision1));
		std::unique_ptr<CPlate> plateCPlate1 = std::make_unique<CPlate>(plate1.get(), true);
		plate1->AddComponent(std::move(plateCPlate1));
		scene.Add(plate1);
	}
	//2//
	const auto plate2 = std::make_shared<GameObject>(std::string{ "plate" });
	plate2->GetTransform()->SetPosition(325, 615);
	plate2->GetTransform()->SetScale(160, 5);
	//std::unique_ptr<CRender> plateCRender2 = std::make_unique<CRender>(plate2.get(), plateTexture);
	//plate2->AddComponent(std::move(plateCRender2));
	std::unique_ptr<CCollisionBox> plateCCollision2 = std::make_unique<CCollisionBox>(plate2.get(), CollisionGroup::Plate);
	plate2->AddComponent(std::move(plateCCollision2));
	std::unique_ptr<CPlate> plateCPlate2 = std::make_unique<CPlate>(plate2.get(), true);
	plate2->AddComponent(std::move(plateCPlate2));
	scene.Add(plate2);
	//3//
	const auto plate3 = std::make_shared<GameObject>(std::string{ "plate" });
	plate3->GetTransform()->SetPosition(185, 615);
	plate3->GetTransform()->SetScale(160, 5);
	//std::unique_ptr<CRender> plateCRender3 = std::make_unique<CRender>(plate3.get(), plateTexture);
	//plate3->AddComponent(std::move(plateCRender3));
	std::unique_ptr<CCollisionBox> plateCCollision3 = std::make_unique<CCollisionBox>(plate3.get(), CollisionGroup::Plate);
	plate3->AddComponent(std::move(plateCCollision3));
	std::unique_ptr<CPlate> plateCPlate3 = std::make_unique<CPlate>(plate3.get(), true);
	plate3->AddComponent(std::move(plateCPlate3));
	scene.Add(plate3);
}

void BurgerTime::CreateTerrainLevel0(Scene& scene)
{

#pragma region Ladders
	//COMMON RESOURCES
	const auto ladderTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//LADDER0
	const auto ladder0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ladder0->GetTransform()->SetPosition(17, 67);
	ladder0->GetTransform()->SetScale(20, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision0 = std::make_unique<CCollisionBox>(ladder0.get(), CollisionGroup::Ladder);
	ladder0->AddComponent(std::move(ladderCCollision0));
	//std::unique_ptr<CRender> ladderCRender0 = std::make_unique<CRender>(ladder0.get(), ladderTexture, true);
	//ladder0->AddComponent(std::move(ladderCRender0));
	scene.Add(ladder0);
	//LADDER1
	const auto ladder1 = std::make_shared<GameObject>(std::string{ "Ladder1" });
	ladder1->GetTransform()->SetPosition(87, 67);
	ladder1->GetTransform()->SetScale(20, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision1 = std::make_unique<CCollisionBox>(ladder1.get(), CollisionGroup::Ladder);
	ladder1->AddComponent(std::move(ladderCCollision1));
	//std::unique_ptr<CRender> ladderCRender1 = std::make_unique<CRender>(ladder1.get(), ladderTexture, true);
	//ladder1->AddComponent(std::move(ladderCRender1));
	scene.Add(ladder1);
	//LADDER2
	const auto ladder2 = std::make_shared<GameObject>(std::string{ "Ladder2" });
	ladder2->GetTransform()->SetPosition(159, 67);
	ladder2->GetTransform()->SetScale(20, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision2 = std::make_unique<CCollisionBox>(ladder2.get(), CollisionGroup::Ladder);
	ladder2->AddComponent(std::move(ladderCCollision2));
	//std::unique_ptr<CRender> ladderCRender2 = std::make_unique<CRender>(ladder2.get(), ladderTexture, true);
	//ladder2->AddComponent(std::move(ladderCRender2));
	scene.Add(ladder2);
	//LADDER3
	const auto ladder3 = std::make_shared<GameObject>(std::string{ "Ladder3" });
	ladder3->GetTransform()->SetPosition(229, 67);
	ladder3->GetTransform()->SetScale(20, 390);
	std::unique_ptr<CCollisionBox> ladderCCollision3 = std::make_unique<CCollisionBox>(ladder3.get(), CollisionGroup::Ladder);
	ladder3->AddComponent(std::move(ladderCCollision3));
	//std::unique_ptr<CRender> ladderCRender3 = std::make_unique<CRender>(ladder3.get(), ladderTexture, true);
	//ladder3->AddComponent(std::move(ladderCRender3));
	scene.Add(ladder3);
	//LADDER4
	const auto ladder4 = std::make_shared<GameObject>(std::string{ "Ladder4" });
	ladder4->GetTransform()->SetPosition(300, 67);
	ladder4->GetTransform()->SetScale(20, 475);
	std::unique_ptr<CCollisionBox> ladderCCollision4 = std::make_unique<CCollisionBox>(ladder4.get(), CollisionGroup::Ladder);
	ladder4->AddComponent(std::move(ladderCCollision4));
	//std::unique_ptr<CRender> ladderCRender4 = std::make_unique<CRender>(ladder4.get(), ladderTexture, true);
	//ladder4->AddComponent(std::move(ladderCRender4));
	scene.Add(ladder4);
	//LADDER5
	const auto ladder5 = std::make_shared<GameObject>(std::string{ "Ladder5" });
	ladder5->GetTransform()->SetPosition(371, 67);
	ladder5->GetTransform()->SetScale(20, 390);
	std::unique_ptr<CCollisionBox> ladderCCollision5 = std::make_unique<CCollisionBox>(ladder5.get(), CollisionGroup::Ladder);
	ladder5->AddComponent(std::move(ladderCCollision5));
	//std::unique_ptr<CRender> ladderCRender5 = std::make_unique<CRender>(ladder5.get(), ladderTexture, true);
	//ladder5->AddComponent(std::move(ladderCRender5));
	scene.Add(ladder5);
	//LADDER6
	const auto ladder6 = std::make_shared<GameObject>(std::string{ "Ladder6" });
	ladder6->GetTransform()->SetPosition(441, 67);
	ladder6->GetTransform()->SetScale(20, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision6 = std::make_unique<CCollisionBox>(ladder6.get(), CollisionGroup::Ladder);
	ladder6->AddComponent(std::move(ladderCCollision6));
	//std::unique_ptr<CRender> ladderCRender6 = std::make_unique<CRender>(ladder6.get(), ladderTexture, true);
	//ladder6->AddComponent(std::move(ladderCRender6));
	scene.Add(ladder6);
	//LADDER7
	const auto ladder7 = std::make_shared<GameObject>(std::string{ "Ladder7" });
	ladder7->GetTransform()->SetPosition(513, 67);
	ladder7->GetTransform()->SetScale(20, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision7 = std::make_unique<CCollisionBox>(ladder7.get(), CollisionGroup::Ladder);
	ladder7->AddComponent(std::move(ladderCCollision7));
	//std::unique_ptr<CRender> ladderCRender7 = std::make_unique<CRender>(ladder7.get(), ladderTexture, true);
	//ladder7->AddComponent(std::move(ladderCRender7));
	scene.Add(ladder7);
	//LADDER8
	const auto ladder8 = std::make_shared<GameObject>(std::string{ "Ladder8" });
	ladder8->GetTransform()->SetPosition(583, 67);
	ladder8->GetTransform()->SetScale(20, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision8 = std::make_unique<CCollisionBox>(ladder8.get(), CollisionGroup::Ladder);
	ladder8->AddComponent(std::move(ladderCCollision8));
	//std::unique_ptr<CRender> ladderCRender8 = std::make_unique<CRender>(ladder8.get(), ladderTexture, true);
	//ladder8->AddComponent(std::move(ladderCRender8));
	scene.Add(ladder8);
#pragma endregion Ladders

#pragma region Ground
	//COMMON RESOURCES
	const auto groundTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//GROUND0
	const auto ground0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground0->GetTransform()->SetPosition(0, 68);
	ground0->GetTransform()->SetScale(630, 1);
	std::unique_ptr<CCollisionBox> groundCCollision0 = std::make_unique<CCollisionBox>(ground0.get(), CollisionGroup::Ground);
	ground0->AddComponent(std::move(groundCCollision0));
	//std::unique_ptr<CRender> groundCTexture0 = std::make_unique<CRender>(ground0.get(), groundTexture, true);
	//ground0->AddComponent(std::move(groundCTexture0));
	scene.Add(ground0);
	//GROUND1
	const auto ground1 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground1->GetTransform()->SetPosition(5, 115);
	ground1->GetTransform()->SetScale(310, 1);
	std::unique_ptr<CCollisionBox> groundCCollision1 = std::make_unique<CCollisionBox>(ground1.get(), CollisionGroup::Ground);
	ground1->AddComponent(std::move(groundCCollision1));
	//std::unique_ptr<CRender> groundCTexture1 = std::make_unique<CRender>(ground1.get(), groundTexture, true);
	//ground1->AddComponent(std::move(groundCTexture1));
	scene.Add(ground1);
	//GROUND2
	const auto ground2 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground2->GetTransform()->SetPosition(5, 162);
	ground2->GetTransform()->SetScale(180, 1);
	std::unique_ptr<CCollisionBox> groundCCollision2 = std::make_unique<CCollisionBox>(ground2.get(), CollisionGroup::Ground);
	ground2->AddComponent(std::move(groundCCollision2));
	//std::unique_ptr<CRender> groundCTexture2 = std::make_unique<CRender>(ground2.get(), groundTexture, true);
	//ground2->AddComponent(std::move(groundCTexture2));
	scene.Add(ground2);
	//GROUND3
	const auto ground3 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground3->GetTransform()->SetPosition(292, 162);
	ground3->GetTransform()->SetScale(321, 1);
	std::unique_ptr<CCollisionBox> groundCCollision3 = std::make_unique<CCollisionBox>(ground3.get(), CollisionGroup::Ground);
	ground3->AddComponent(std::move(groundCCollision3));
	//std::unique_ptr<CRender> groundCTexture3 = std::make_unique<CRender>(ground3.get(), groundTexture, true);
	//ground3->AddComponent(std::move(groundCTexture3));
	scene.Add(ground3);
	//GROUND4
	const auto ground4 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground4->GetTransform()->SetPosition(152, 210);
	ground4->GetTransform()->SetScale(190, 1);
	std::unique_ptr<CCollisionBox> groundCCollision4 = std::make_unique<CCollisionBox>(ground4.get(), CollisionGroup::Ground);
	ground4->AddComponent(std::move(groundCCollision4));
	//std::unique_ptr<CRender> groundCTexture4 = std::make_unique<CRender>(ground4.get(), groundTexture, true);
	//ground4->AddComponent(std::move(groundCTexture4));
	scene.Add(ground4);
	//GROUND5
	const auto ground5 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground5->GetTransform()->SetPosition(358, 210);
	ground5->GetTransform()->SetScale(243, 1);
	std::unique_ptr<CCollisionBox> groundCCollision5 = std::make_unique<CCollisionBox>(ground5.get(), CollisionGroup::Ground);
	ground5->AddComponent(std::move(groundCCollision5));
	//std::unique_ptr<CRender> groundCTexture5 = std::make_unique<CRender>(ground5.get(), groundTexture, true);
	//ground5->AddComponent(std::move(groundCTexture5));
	scene.Add(ground5);
	//GROUND6
	const auto ground6 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground6->GetTransform()->SetPosition(5, 257);
	ground6->GetTransform()->SetScale(620, 1);
	std::unique_ptr<CCollisionBox> groundCCollision6 = std::make_unique<CCollisionBox>(ground6.get(), CollisionGroup::Ground);
	ground6->AddComponent(std::move(groundCCollision6));
	//std::unique_ptr<CRender> groundCTexture6 = std::make_unique<CRender>(ground6.get(), groundTexture, true);
	//ground6->AddComponent(std::move(groundCTexture6));
	scene.Add(ground6);
	//GROUND7
	const auto ground7 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground7->GetTransform()->SetPosition(312, 304);
	ground7->GetTransform()->SetScale(160, 1);
	std::unique_ptr<CCollisionBox> groundCCollision7 = std::make_unique<CCollisionBox>(ground7.get(), CollisionGroup::Ground);
	ground7->AddComponent(std::move(groundCCollision7));
	//std::unique_ptr<CRender> groundCTexture7 = std::make_unique<CRender>(ground7.get(), groundTexture, true);
	//ground7->AddComponent(std::move(groundCTexture7));
	scene.Add(ground7);
	//GROUND8
	const auto ground8 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground8->GetTransform()->SetPosition(152, 351);
	ground8->GetTransform()->SetScale(160, 1);
	std::unique_ptr<CCollisionBox> groundCCollision8 = std::make_unique<CCollisionBox>(ground8.get(), CollisionGroup::Ground);
	ground8->AddComponent(std::move(groundCCollision8));
	//std::unique_ptr<CRender> groundCTexture8 = std::make_unique<CRender>(ground8.get(), groundTexture, true);
	//ground8->AddComponent(std::move(groundCTexture8));
	scene.Add(ground8);
	//GROUND9
	const auto ground9 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground9->GetTransform()->SetPosition(292, 399);
	ground9->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision9 = std::make_unique<CCollisionBox>(ground9.get(), CollisionGroup::Ground);
	ground9->AddComponent(std::move(groundCCollision9));
	//std::unique_ptr<CRender> groundCTexture9 = std::make_unique<CRender>(ground9.get(), groundTexture, true);
	//ground9->AddComponent(std::move(groundCTexture9));
	scene.Add(ground9);
	//GROUND10
	const auto ground10 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground10->GetTransform()->SetPosition(151, 446);
	ground10->GetTransform()->SetScale(321, 1);
	std::unique_ptr<CCollisionBox> groundCCollision10 = std::make_unique<CCollisionBox>(ground10.get(), CollisionGroup::Ground);
	ground10->AddComponent(std::move(groundCCollision10));
	//std::unique_ptr<CRender> groundCTexture10 = std::make_unique<CRender>(ground10.get(), groundTexture, true);
	//ground10->AddComponent(std::move(groundCTexture10));
	scene.Add(ground10);
	//GROUND11
	const auto ground11 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground11->GetTransform()->SetPosition(292, 541);
	ground11->GetTransform()->SetScale(35, 1);
	std::unique_ptr<CCollisionBox> groundCCollision11 = std::make_unique<CCollisionBox>(ground11.get(), CollisionGroup::Ground);
	ground11->AddComponent(std::move(groundCCollision11));
	//std::unique_ptr<CRender> groundCTexture11 = std::make_unique<CRender>(ground11.get(), groundTexture, true);
	//ground11->AddComponent(std::move(groundCTexture11));
	scene.Add(ground11);
#pragma endregion Ground
}

void BurgerTime::CreateTerrainLevel1(Scene& scene)
{
	//COMMON RESOURCES
	const auto ladderTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//LADDER0
	const auto ladder0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ladder0->GetTransform()->SetPosition(17, 67);
	ladder0->GetTransform()->SetScale(20, 100);
	std::unique_ptr<CCollisionBox> ladderCCollision0 = std::make_unique<CCollisionBox>(ladder0.get(), CollisionGroup::Ladder);
	ladder0->AddComponent(std::move(ladderCCollision0));
	//std::unique_ptr<CRender> ladderCRender0 = std::make_unique<CRender>(ladder0.get(), ladderTexture, true);
	//ladder0->AddComponent(std::move(ladderCRender0));
	scene.Add(ladder0);
	//LADDER1
	const auto ladder1 = std::make_shared<GameObject>(std::string{ "Ladder1" });
	ladder1->GetTransform()->SetPosition(87, 162);
	ladder1->GetTransform()->SetScale(20, 250);
	std::unique_ptr<CCollisionBox> ladderCCollision1 = std::make_unique<CCollisionBox>(ladder1.get(), CollisionGroup::Ladder);
	ladder1->AddComponent(std::move(ladderCCollision1));
	//std::unique_ptr<CRender> ladderCRender1 = std::make_unique<CRender>(ladder1.get(), ladderTexture, true);
	//ladder1->AddComponent(std::move(ladderCRender1));
	scene.Add(ladder1);
	//LADDER2
	const auto ladder2 = std::make_shared<GameObject>(std::string{ "Ladder2" });
	ladder2->GetTransform()->SetPosition(159, 67);
	ladder2->GetTransform()->SetScale(20, 430);
	std::unique_ptr<CCollisionBox> ladderCCollision2 = std::make_unique<CCollisionBox>(ladder2.get(), CollisionGroup::Ladder);
	ladder2->AddComponent(std::move(ladderCCollision2));
	//std::unique_ptr<CRender> ladderCRender2 = std::make_unique<CRender>(ladder2.get(), ladderTexture, true);
	//ladder2->AddComponent(std::move(ladderCRender2));
	scene.Add(ladder2);
	//LADDER3
	const auto ladder3 = std::make_shared<GameObject>(std::string{ "Ladder3" });
	ladder3->GetTransform()->SetPosition(229, 67);
	ladder3->GetTransform()->SetScale(20, 140);
	std::unique_ptr<CCollisionBox> ladderCCollision3 = std::make_unique<CCollisionBox>(ladder3.get(), CollisionGroup::Ladder);
	ladder3->AddComponent(std::move(ladderCCollision3));
	//std::unique_ptr<CRender> ladderCRender3 = std::make_unique<CRender>(ladder3.get(), ladderTexture, true);
	//ladder3->AddComponent(std::move(ladderCRender3));
	scene.Add(ladder3);
	//LADDER4
	const auto ladder4 = std::make_shared<GameObject>(std::string{ "Ladder4" });
	ladder4->GetTransform()->SetPosition(300, 67);
	ladder4->GetTransform()->SetScale(20, 430);
	std::unique_ptr<CCollisionBox> ladderCCollision4 = std::make_unique<CCollisionBox>(ladder4.get(), CollisionGroup::Ladder);
	ladder4->AddComponent(std::move(ladderCCollision4));
	//std::unique_ptr<CRender> ladderCRender4 = std::make_unique<CRender>(ladder4.get(), ladderTexture, true);
	//ladder4->AddComponent(std::move(ladderCRender4));
	scene.Add(ladder4);
	//LADDER5
	const auto ladder5 = std::make_shared<GameObject>(std::string{ "Ladder5" });
	ladder5->GetTransform()->SetPosition(371, 162);
	ladder5->GetTransform()->SetScale(20, 140);
	std::unique_ptr<CCollisionBox> ladderCCollision5 = std::make_unique<CCollisionBox>(ladder5.get(), CollisionGroup::Ladder);
	ladder5->AddComponent(std::move(ladderCCollision5));
	//std::unique_ptr<CRender> ladderCRender5 = std::make_unique<CRender>(ladder5.get(), ladderTexture, true);
	//ladder5->AddComponent(std::move(ladderCRender5));
	scene.Add(ladder5);
	//LADDER6
	const auto ladder6 = std::make_shared<GameObject>(std::string{ "Ladder6" });
	ladder6->GetTransform()->SetPosition(441, 67);
	ladder6->GetTransform()->SetScale(20, 430);
	std::unique_ptr<CCollisionBox> ladderCCollision6 = std::make_unique<CCollisionBox>(ladder6.get(), CollisionGroup::Ladder);
	ladder6->AddComponent(std::move(ladderCCollision6));
	//std::unique_ptr<CRender> ladderCRender6 = std::make_unique<CRender>(ladder6.get(), ladderTexture, true);
	//ladder6->AddComponent(std::move(ladderCRender6));
	scene.Add(ladder6);
	//LADDER7
	const auto ladder7 = std::make_shared<GameObject>(std::string{ "Ladder7" });
	ladder7->GetTransform()->SetPosition(513, 260);
	ladder7->GetTransform()->SetScale(20, 240);
	std::unique_ptr<CCollisionBox> ladderCCollision7 = std::make_unique<CCollisionBox>(ladder7.get(), CollisionGroup::Ladder);
	ladder7->AddComponent(std::move(ladderCCollision7));
	//std::unique_ptr<CRender> ladderCRender7 = std::make_unique<CRender>(ladder7.get(), ladderTexture, true);
	//ladder7->AddComponent(std::move(ladderCRender7));
	scene.Add(ladder7);
	//LADDER8
	const auto ladder8 = std::make_shared<GameObject>(std::string{ "Ladder8" });
	ladder8->GetTransform()->SetPosition(583, 67);
	ladder8->GetTransform()->SetScale(20, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision8 = std::make_unique<CCollisionBox>(ladder8.get(), CollisionGroup::Ladder);
	ladder8->AddComponent(std::move(ladderCCollision8));
	//std::unique_ptr<CRender> ladderCRender8 = std::make_unique<CRender>(ladder8.get(), ladderTexture, true);
	//ladder8->AddComponent(std::move(ladderCRender8));
	scene.Add(ladder8);
	//LADDER9
	const auto ladder9 = std::make_shared<GameObject>(std::string{ "Ladder8" });
	ladder9->GetTransform()->SetPosition(17, 260);
	ladder9->GetTransform()->SetScale(20, 240);
	std::unique_ptr<CCollisionBox> ladderCCollision9 = std::make_unique<CCollisionBox>(ladder9.get(), CollisionGroup::Ladder);
	ladder9->AddComponent(std::move(ladderCCollision9));
	//std::unique_ptr<CRender> ladderCRender9 = std::make_unique<CRender>(ladder9.get(), ladderTexture, true);
	//ladder9->AddComponent(std::move(ladderCRender9));
	scene.Add(ladder9);
	//LADDER10
	const auto ladder10 = std::make_shared<GameObject>(std::string{ "Ladder8" });
	ladder10->GetTransform()->SetPosition(583, 355);
	ladder10->GetTransform()->SetScale(20, 162);
	std::unique_ptr<CCollisionBox> ladderCCollision10 = std::make_unique<CCollisionBox>(ladder10.get(), CollisionGroup::Ladder);
	ladder10->AddComponent(std::move(ladderCCollision10));
	//std::unique_ptr<CRender> ladderCRender10 = std::make_unique<CRender>(ladder10.get(), ladderTexture, true);
	//ladder10->AddComponent(std::move(ladderCRender10));
	scene.Add(ladder10);


		//COMMON RESOURCES
	const auto groundTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//GROUND0
	const auto ground0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground0->GetTransform()->SetPosition(0, 68);
	ground0->GetTransform()->SetScale(630, 1);
	std::unique_ptr<CCollisionBox> groundCCollision0 = std::make_unique<CCollisionBox>(ground0.get(), CollisionGroup::Ground);
	ground0->AddComponent(std::move(groundCCollision0));
	//std::unique_ptr<CRender> groundCTexture0 = std::make_unique<CRender>(ground0.get(), groundTexture, true);
	//ground0->AddComponent(std::move(groundCTexture0));
	scene.Add(ground0);
	//GROUND2
	const auto ground2 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground2->GetTransform()->SetPosition(5, 162);
	ground2->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision2 = std::make_unique<CCollisionBox>(ground2.get(), CollisionGroup::Ground);
	ground2->AddComponent(std::move(groundCCollision2));
	//std::unique_ptr<CRender> groundCTexture2 = std::make_unique<CRender>(ground2.get(), groundTexture, true);
	//ground2->AddComponent(std::move(groundCTexture2));
	scene.Add(ground2);
	//GROUND3
	const auto ground3 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground3->GetTransform()->SetPosition(292, 162);
	ground3->GetTransform()->SetScale(321, 1);
	std::unique_ptr<CCollisionBox> groundCCollision3 = std::make_unique<CCollisionBox>(ground3.get(), CollisionGroup::Ground);
	ground3->AddComponent(std::move(groundCCollision3));
	//std::unique_ptr<CRender> groundCTexture3 = std::make_unique<CRender>(ground3.get(), groundTexture, true);
	//ground3->AddComponent(std::move(groundCTexture3));
	scene.Add(ground3);
	//GROUND5
	const auto ground5 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground5->GetTransform()->SetPosition(150, 210);
	ground5->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision5 = std::make_unique<CCollisionBox>(ground5.get(), CollisionGroup::Ground);
	ground5->AddComponent(std::move(groundCCollision5));
	//std::unique_ptr<CRender> groundCTexture5 = std::make_unique<CRender>(ground5.get(), groundTexture, true);
	//ground5->AddComponent(std::move(groundCTexture5));
	scene.Add(ground5);
	//GROUND6
	const auto ground6 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground6->GetTransform()->SetPosition(5, 257);
	ground6->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision6 = std::make_unique<CCollisionBox>(ground6.get(), CollisionGroup::Ground);
	ground6->AddComponent(std::move(groundCCollision6));
	//std::unique_ptr<CRender> groundCTexture6 = std::make_unique<CRender>(ground6.get(), groundTexture, true);
	//ground6->AddComponent(std::move(groundCTexture6));
	scene.Add(ground6);
	//GROUND6bis
	const auto ground62 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground62->GetTransform()->SetPosition(440, 257);
	ground62->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision62 = std::make_unique<CCollisionBox>(ground62.get(), CollisionGroup::Ground);
	ground62->AddComponent(std::move(groundCCollision62));
	//std::unique_ptr<CRender> groundCTexture62 = std::make_unique<CRender>(ground62.get(), groundTexture, true);
	//ground62->AddComponent(std::move(groundCTexture62));
	scene.Add(ground62);
	//GROUND7
	const auto ground7 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground7->GetTransform()->SetPosition(155, 304);
	ground7->GetTransform()->SetScale(310, 1);
	std::unique_ptr<CCollisionBox> groundCCollision7 = std::make_unique<CCollisionBox>(ground7.get(), CollisionGroup::Ground);
	ground7->AddComponent(std::move(groundCCollision7));
	//std::unique_ptr<CRender> groundCTexture7 = std::make_unique<CRender>(ground7.get(), groundTexture, true);
	//ground7->AddComponent(std::move(groundCTexture7));
	scene.Add(ground7);
	//GROUND8
	const auto ground8 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground8->GetTransform()->SetPosition(452, 351);
	ground8->GetTransform()->SetScale(160, 1);
	std::unique_ptr<CCollisionBox> groundCCollision8 = std::make_unique<CCollisionBox>(ground8.get(), CollisionGroup::Ground);
	ground8->AddComponent(std::move(groundCCollision8));
	//std::unique_ptr<CRender> groundCTexture8 = std::make_unique<CRender>(ground8.get(), groundTexture, true);
	//ground8->AddComponent(std::move(groundCTexture8));
	scene.Add(ground8);
	//GROUND9
	const auto ground9 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground9->GetTransform()->SetPosition(5, 399);
	ground9->GetTransform()->SetScale(450, 1);
	std::unique_ptr<CCollisionBox> groundCCollision9 = std::make_unique<CCollisionBox>(ground9.get(), CollisionGroup::Ground);
	ground9->AddComponent(std::move(groundCCollision9));
	//std::unique_ptr<CRender> groundCTexture9 = std::make_unique<CRender>(ground9.get(), groundTexture, true);
	//ground9->AddComponent(std::move(groundCTexture9));
	scene.Add(ground9);
	//GROUND10
	const auto ground10 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground10->GetTransform()->SetPosition(5, 490);
	ground10->GetTransform()->SetScale(620, 1);
	std::unique_ptr<CCollisionBox> groundCCollision10 = std::make_unique<CCollisionBox>(ground10.get(), CollisionGroup::Ground);
	ground10->AddComponent(std::move(groundCCollision10));
	//std::unique_ptr<CRender> groundCTexture10 = std::make_unique<CRender>(ground10.get(), groundTexture, true);
	//ground10->AddComponent(std::move(groundCTexture10));
	scene.Add(ground10);
}

void BurgerTime::CreateTerrainLevel2(Scene& scene)
{
	//COMMON RESOURCES
	const auto groundTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//GROUND2
	const auto ground2 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground2->GetTransform()->SetPosition(5, 112);
	ground2->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision2 = std::make_unique<CCollisionBox>(ground2.get(), CollisionGroup::Ground);
	ground2->AddComponent(std::move(groundCCollision2));
	//std::unique_ptr<CRender> groundCTexture2 = std::make_unique<CRender>(ground2.get(), groundTexture, true);
	//ground2->AddComponent(std::move(groundCTexture2));
	scene.Add(ground2);
	//GROUND21
	const auto ground21 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground21->GetTransform()->SetPosition(5, 210);
	ground21->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision21 = std::make_unique<CCollisionBox>(ground21.get(), CollisionGroup::Ground);
	ground21->AddComponent(std::move(groundCCollision21));
	//std::unique_ptr<CRender> groundCTexture21 = std::make_unique<CRender>(ground21.get(), groundTexture, true);
	//ground21->AddComponent(std::move(groundCTexture21));
	scene.Add(ground21);
	////GROUND22
	const auto ground22 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground22->GetTransform()->SetPosition(5, 304);
	ground22->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision22 = std::make_unique<CCollisionBox>(ground22.get(), CollisionGroup::Ground);
	ground22->AddComponent(std::move(groundCCollision22));
	//std::unique_ptr<CRender> groundCTexture22 = std::make_unique<CRender>(ground22.get(), groundTexture, true);
	//ground22->AddComponent(std::move(groundCTexture22));
	scene.Add(ground22);
	//GROUND23
	const auto ground23 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground23->GetTransform()->SetPosition(5, 396);
	ground23->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision23 = std::make_unique<CCollisionBox>(ground23.get(), CollisionGroup::Ground);
	ground23->AddComponent(std::move(groundCCollision23));
	//std::unique_ptr<CRender> groundCTexture23 = std::make_unique<CRender>(ground23.get(), groundTexture, true);
	//ground23->AddComponent(std::move(groundCTexture23));
	scene.Add(ground23);
	//GROUND24
	const auto ground24 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground24->GetTransform()->SetPosition(5, 494);
	ground24->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision24 = std::make_unique<CCollisionBox>(ground24.get(), CollisionGroup::Ground);
	ground24->AddComponent(std::move(groundCCollision24));
	//std::unique_ptr<CRender> groundCTexture24 = std::make_unique<CRender>(ground24.get(), groundTexture, true);
	//ground24->AddComponent(std::move(groundCTexture24));
	scene.Add(ground24);
	//GROUND4
	const auto ground4 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground4->GetTransform()->SetPosition(152, 68);
	ground4->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision4 = std::make_unique<CCollisionBox>(ground4.get(), CollisionGroup::Ground);
	ground4->AddComponent(std::move(groundCCollision4));
	//std::unique_ptr<CRender> groundCTexture4 = std::make_unique<CRender>(ground4.get(), groundTexture, true);
	//ground4->AddComponent(std::move(groundCTexture4));
	scene.Add(ground4);
	//GROUND21
	const auto ground41 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground41->GetTransform()->SetPosition(152, 160);
	ground41->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision41 = std::make_unique<CCollisionBox>(ground41.get(), CollisionGroup::Ground);
	ground41->AddComponent(std::move(groundCCollision41));
	//std::unique_ptr<CRender> groundCTexture41 = std::make_unique<CRender>(ground41.get(), groundTexture, true);
	//ground41->AddComponent(std::move(groundCTexture41));
	scene.Add(ground41);
	////GROUND22
	const auto ground42 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground42->GetTransform()->SetPosition(152, 254);
	ground42->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision42 = std::make_unique<CCollisionBox>(ground42.get(), CollisionGroup::Ground);
	ground42->AddComponent(std::move(groundCCollision42));
	//std::unique_ptr<CRender> groundCTexture42 = std::make_unique<CRender>(ground42.get(), groundTexture, true);
	//ground42->AddComponent(std::move(groundCTexture42));
	scene.Add(ground42);
	//GROUND23
	const auto ground43 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground43->GetTransform()->SetPosition(152, 346);
	ground43->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision43 = std::make_unique<CCollisionBox>(ground43.get(), CollisionGroup::Ground);
	ground43->AddComponent(std::move(groundCCollision43));
	//std::unique_ptr<CRender> groundCTexture43 = std::make_unique<CRender>(ground43.get(), groundTexture, true);
	//ground43->AddComponent(std::move(groundCTexture43));
	scene.Add(ground43);
	//GROUND24
	const auto ground44 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground44->GetTransform()->SetPosition(152, 444);
	ground44->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision44 = std::make_unique<CCollisionBox>(ground44.get(), CollisionGroup::Ground);
	ground44->AddComponent(std::move(groundCCollision44));
	//std::unique_ptr<CRender> groundCTexture44 = std::make_unique<CRender>(ground44.get(), groundTexture, true);
	//ground44->AddComponent(std::move(groundCTexture44));
	scene.Add(ground44);
	//GROUND5
	const auto ground5 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground5->GetTransform()->SetPosition(295, 112);
	ground5->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision5 = std::make_unique<CCollisionBox>(ground5.get(), CollisionGroup::Ground);
	ground5->AddComponent(std::move(groundCCollision5));
	//std::unique_ptr<CRender> groundCTexture5 = std::make_unique<CRender>(ground5.get(), groundTexture, true);
	//ground5->AddComponent(std::move(groundCTexture5));
	scene.Add(ground5);
	//GROUND21
	const auto ground51 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground51->GetTransform()->SetPosition(295, 210);
	ground51->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision51 = std::make_unique<CCollisionBox>(ground51.get(), CollisionGroup::Ground);
	ground51->AddComponent(std::move(groundCCollision51));
	//std::unique_ptr<CRender> groundCTexture51 = std::make_unique<CRender>(ground51.get(), groundTexture, true);
	//ground51->AddComponent(std::move(groundCTexture51));
	scene.Add(ground51);
	////GROUND22
	const auto ground52 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground52->GetTransform()->SetPosition(295, 304);
	ground52->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision52 = std::make_unique<CCollisionBox>(ground52.get(), CollisionGroup::Ground);
	ground52->AddComponent(std::move(groundCCollision52));
	//std::unique_ptr<CRender> groundCTexture52 = std::make_unique<CRender>(ground52.get(), groundTexture, true);
	//ground52->AddComponent(std::move(groundCTexture52));
	scene.Add(ground52);
	//GROUND23
	const auto ground53 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground53->GetTransform()->SetPosition(295, 396);
	ground53->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision53 = std::make_unique<CCollisionBox>(ground53.get(), CollisionGroup::Ground);
	ground53->AddComponent(std::move(groundCCollision53));
	//std::unique_ptr<CRender> groundCTexture53 = std::make_unique<CRender>(ground53.get(), groundTexture, true);
	//ground53->AddComponent(std::move(groundCTexture53));
	scene.Add(ground53);
	//GROUND24
	const auto ground54 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground54->GetTransform()->SetPosition(295, 494);
	ground54->GetTransform()->SetScale(175, 1);
	std::unique_ptr<CCollisionBox> groundCCollision54 = std::make_unique<CCollisionBox>(ground54.get(), CollisionGroup::Ground);
	ground54->AddComponent(std::move(groundCCollision54));
	//std::unique_ptr<CRender> groundCTexture54 = std::make_unique<CRender>(ground54.get(), groundTexture, true);
	//ground54->AddComponent(std::move(groundCTexture54));
	scene.Add(ground54);
	//GROUND7
	const auto ground7 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground7->GetTransform()->SetPosition(445, 68);
	ground7->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision7= std::make_unique<CCollisionBox>(ground7.get(), CollisionGroup::Ground);
	ground7->AddComponent(std::move(groundCCollision7));
	//std::unique_ptr<CRender> groundCTexture7 = std::make_unique<CRender>(ground7.get(), groundTexture, true);
	//ground7->AddComponent(std::move(groundCTexture7));
	scene.Add(ground7);
	//GROUND21
	const auto ground71 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground71->GetTransform()->SetPosition(445, 160);
	ground71->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision71 = std::make_unique<CCollisionBox>(ground71.get(), CollisionGroup::Ground);
	ground71->AddComponent(std::move(groundCCollision71));
	//std::unique_ptr<CRender> groundCTexture71 = std::make_unique<CRender>(ground71.get(), groundTexture, true);
	//ground71->AddComponent(std::move(groundCTexture71));
	scene.Add(ground71);
	////GROUND22
	const auto ground72 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground72->GetTransform()->SetPosition(445, 254);
	ground72->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision72 = std::make_unique<CCollisionBox>(ground72.get(), CollisionGroup::Ground);
	ground72->AddComponent(std::move(groundCCollision72));
	//std::unique_ptr<CRender> groundCTexture72 = std::make_unique<CRender>(ground72.get(), groundTexture, true);
	//ground72->AddComponent(std::move(groundCTexture72));
	scene.Add(ground72);
	//GROUND23
	const auto ground73 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground73->GetTransform()->SetPosition(445, 346);
	ground73->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision73 = std::make_unique<CCollisionBox>(ground73.get(), CollisionGroup::Ground);
	ground73->AddComponent(std::move(groundCCollision73));
	//std::unique_ptr<CRender> groundCTexture73 = std::make_unique<CRender>(ground73.get(), groundTexture, true);
	//ground73->AddComponent(std::move(groundCTexture73));
	scene.Add(ground73);
	//GROUND24
	const auto ground74 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground74->GetTransform()->SetPosition(445, 444);
	ground74->GetTransform()->SetScale(170, 1);
	std::unique_ptr<CCollisionBox> groundCCollision74 = std::make_unique<CCollisionBox>(ground74.get(), CollisionGroup::Ground);
	ground74->AddComponent(std::move(groundCCollision74));
	//std::unique_ptr<CRender> groundCTexture74 = std::make_unique<CRender>(ground74.get(), groundTexture, true);
	//ground74->AddComponent(std::move(groundCTexture74));
	scene.Add(ground74);

	//COMMON RESOURCES
	const auto ladderTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//LADDER2
	const auto ladder2 = std::make_shared<GameObject>(std::string{ "Ladder2" });
	ladder2->GetTransform()->SetPosition(159, 67);
	ladder2->GetTransform()->SetScale(20, 150);
	std::unique_ptr<CCollisionBox> ladderCCollision2 = std::make_unique<CCollisionBox>(ladder2.get(), CollisionGroup::Ladder);
	ladder2->AddComponent(std::move(ladderCCollision2));
	//std::unique_ptr<CRender> ladderCRender2 = std::make_unique<CRender>(ladder2.get(), ladderTexture, true);
	//ladder2->AddComponent(std::move(ladderCRender2));
	scene.Add(ladder2);
	//LADDER21
	const auto ladder21 = std::make_shared<GameObject>(std::string{ "Ladder2" });
	ladder21->GetTransform()->SetPosition(159, 252);
	ladder21->GetTransform()->SetScale(20, 155);
	std::unique_ptr<CCollisionBox> ladderCCollision21 = std::make_unique<CCollisionBox>(ladder21.get(), CollisionGroup::Ladder);
	ladder21->AddComponent(std::move(ladderCCollision21));
	//std::unique_ptr<CRender> ladderCRender21 = std::make_unique<CRender>(ladder21.get(), ladderTexture, true);
	//ladder21->AddComponent(std::move(ladderCRender21));
	scene.Add(ladder21);
	//LADDER21
	const auto ladder22 = std::make_shared<GameObject>(std::string{ "Ladder2" });
	ladder22->GetTransform()->SetPosition(159, 440);
	ladder22->GetTransform()->SetScale(20, 60);
	std::unique_ptr<CCollisionBox> ladderCCollision22 = std::make_unique<CCollisionBox>(ladder22.get(), CollisionGroup::Ladder);
	ladder22->AddComponent(std::move(ladderCCollision22));
	//std::unique_ptr<CRender> ladderCRender22 = std::make_unique<CRender>(ladder22.get(), ladderTexture, true);
	//ladder22->AddComponent(std::move(ladderCRender22));
	scene.Add(ladder22);
	//LADDER3
	const auto ladder31 = std::make_shared<GameObject>(std::string{ "Ladder3" });
	ladder31->GetTransform()->SetPosition(229, 350);
	ladder31->GetTransform()->SetScale(20, 100);
	std::unique_ptr<CCollisionBox> ladderCCollision31 = std::make_unique<CCollisionBox>(ladder31.get(), CollisionGroup::Ladder);
	ladder31->AddComponent(std::move(ladderCCollision31));
	//std::unique_ptr<CRender> ladderCRender31 = std::make_unique<CRender>(ladder31.get(), ladderTexture, true);
	//ladder31->AddComponent(std::move(ladderCRender31));
	scene.Add(ladder31);
	//LADDER3
	const auto ladder3 = std::make_shared<GameObject>(std::string{ "Ladder3" });
	ladder3->GetTransform()->SetPosition(229, 67);
	ladder3->GetTransform()->SetScale(20, 210);
	std::unique_ptr<CCollisionBox> ladderCCollision3 = std::make_unique<CCollisionBox>(ladder3.get(), CollisionGroup::Ladder);
	ladder3->AddComponent(std::move(ladderCCollision3));
	//std::unique_ptr<CRender> ladderCRender3 = std::make_unique<CRender>(ladder3.get(), ladderTexture, true);
	//ladder3->AddComponent(std::move(ladderCRender3));
	scene.Add(ladder3);
	//LADDER4
	const auto ladder4 = std::make_shared<GameObject>(std::string{ "Ladder4" });
	ladder4->GetTransform()->SetPosition(300, 160);
	ladder4->GetTransform()->SetScale(20, 145);
	std::unique_ptr<CCollisionBox> ladderCCollision4 = std::make_unique<CCollisionBox>(ladder4.get(), CollisionGroup::Ladder);
	ladder4->AddComponent(std::move(ladderCCollision4));
	//std::unique_ptr<CRender> ladderCRender4 = std::make_unique<CRender>(ladder4.get(), ladderTexture, true);
	//ladder4->AddComponent(std::move(ladderCRender4));
	scene.Add(ladder4);
	//LADDER4
	const auto ladder41 = std::make_shared<GameObject>(std::string{ "Ladder4" });
	ladder41->GetTransform()->SetPosition(300, 350);
	ladder41->GetTransform()->SetScale(20, 145);
	std::unique_ptr<CCollisionBox> ladderCCollision41 = std::make_unique<CCollisionBox>(ladder41.get(), CollisionGroup::Ladder);
	ladder41->AddComponent(std::move(ladderCCollision41));
	//std::unique_ptr<CRender> ladderCRender41 = std::make_unique<CRender>(ladder41.get(), ladderTexture, true);
	//ladder41->AddComponent(std::move(ladderCRender41));
	scene.Add(ladder41);
	//LADDER5
	const auto ladder5 = std::make_shared<GameObject>(std::string{ "Ladder5" });
	ladder5->GetTransform()->SetPosition(371, 107);
	ladder5->GetTransform()->SetScale(20, 110);
	std::unique_ptr<CCollisionBox> ladderCCollision5 = std::make_unique<CCollisionBox>(ladder5.get(), CollisionGroup::Ladder);
	ladder5->AddComponent(std::move(ladderCCollision5));
	//std::unique_ptr<CRender> ladderCRender5 = std::make_unique<CRender>(ladder5.get(), ladderTexture, true);
	//ladder5->AddComponent(std::move(ladderCRender5));
	scene.Add(ladder5);
	//LADDER5
	const auto ladder51 = std::make_shared<GameObject>(std::string{ "Ladder5" });
	ladder51->GetTransform()->SetPosition(371, 280);
	ladder51->GetTransform()->SetScale(20, 240);
	std::unique_ptr<CCollisionBox> ladderCCollision51 = std::make_unique<CCollisionBox>(ladder51.get(), CollisionGroup::Ladder);
	ladder51->AddComponent(std::move(ladderCCollision51));
	//std::unique_ptr<CRender> ladderCRender51 = std::make_unique<CRender>(ladder51.get(), ladderTexture, true);
	//ladder51->AddComponent(std::move(ladderCRender51));
	scene.Add(ladder51);
	//LADDER6
	const auto ladder6 = std::make_shared<GameObject>(std::string{ "Ladder6" });
	ladder6->GetTransform()->SetPosition(441, 67);
	ladder6->GetTransform()->SetScale(20, 50);
	std::unique_ptr<CCollisionBox> ladderCCollision6 = std::make_unique<CCollisionBox>(ladder6.get(), CollisionGroup::Ladder);
	ladder6->AddComponent(std::move(ladderCCollision6));
	//std::unique_ptr<CRender> ladderCRender6 = std::make_unique<CRender>(ladder6.get(), ladderTexture, true);
	//ladder6->AddComponent(std::move(ladderCRender6));
	scene.Add(ladder6);
	//LADDER6
	const auto ladder61 = std::make_shared<GameObject>(std::string{ "Ladder6" });
	ladder61->GetTransform()->SetPosition(441, 160);
	ladder61->GetTransform()->SetScale(20, 150);
	std::unique_ptr<CCollisionBox> ladderCCollision61 = std::make_unique<CCollisionBox>(ladder61.get(), CollisionGroup::Ladder);
	ladder61->AddComponent(std::move(ladderCCollision61));
	//std::unique_ptr<CRender> ladderCRender61 = std::make_unique<CRender>(ladder61.get(), ladderTexture, true);
	//ladder61->AddComponent(std::move(ladderCRender61));
	scene.Add(ladder61);
	//LADDER6
	const auto ladder62 = std::make_shared<GameObject>(std::string{ "Ladder6" });
	ladder62->GetTransform()->SetPosition(441, 350);
	ladder62->GetTransform()->SetScale(20, 150);
	std::unique_ptr<CCollisionBox> ladderCCollision62 = std::make_unique<CCollisionBox>(ladder62.get(), CollisionGroup::Ladder);
	ladder62->AddComponent(std::move(ladderCCollision62));
	//std::unique_ptr<CRender> ladderCRender62 = std::make_unique<CRender>(ladder62.get(), ladderTexture, true);
	//ladder62->AddComponent(std::move(ladderCRender62));
	scene.Add(ladder62);
}


std::vector<InputManager*> BurgerTime::ConfigureInput()
{
	std::vector<InputManager*> inputManagers;

	//INPUT PAWN ONE
	InputManager* inputPlayerOne = new InputManager{ 0 };
	inputPlayerOne->BindCommandToButton(ControllerButton::DPadRight, std::make_unique<MoveRight>());
	inputPlayerOne->BindCommandToButton(ControllerButton::DPadLeft, std::make_unique<MoveLeft>());
	inputPlayerOne->BindCommandToButton(ControllerButton::DPadUp, std::make_unique<ClimbUp>());
	inputPlayerOne->BindCommandToButton(ControllerButton::DPadDown, std::make_unique<ClimbDown>());

	inputPlayerOne->SetPawn(m_pPlayerOnePawn);
	inputManagers.push_back(inputPlayerOne);

	if (m_GameMode != "Singleplayer")
	{
		//INPUT PAWN TWO
		InputManager* inputPlayerTwo = new InputManager{ 0 };
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_RIGHT, std::make_unique<MoveRight>());
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_LEFT, std::make_unique<MoveLeft>());
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_UP, std::make_unique<ClimbUp>());
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_DOWN, std::make_unique<ClimbDown>());

		inputPlayerTwo->SetPawn(m_pPlayerTwoPawn);
		inputManagers.push_back(inputPlayerTwo);
	}
	else
	{
		//INPUT PAWN TWO
		InputManager* inputPlayerTwo = new InputManager{ 0 };
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_RIGHT, std::make_unique<MoveRight>());
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_LEFT, std::make_unique<MoveLeft>());
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_UP, std::make_unique<ClimbUp>());
		inputPlayerTwo->BindCommandToButton(SDL_SCANCODE_DOWN, std::make_unique<ClimbDown>());

		inputPlayerTwo->SetPawn(m_pPlayerOnePawn);
		inputManagers.push_back(inputPlayerTwo);
	}

	return inputManagers;
}