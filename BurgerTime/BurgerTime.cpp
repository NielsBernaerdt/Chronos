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
//Observers
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
	m_NPCLocations.push_back(glm::vec3{175, 300, 0});
	//npc 04
	m_NPCLocations.push_back(glm::vec3{500, 100, 0});
	//npc 05
	m_NPCLocations.push_back(glm::vec3{200, 200, 0});
	//npc 06
	m_NPCLocations.push_back(glm::vec3{50, 400, 0});
}


void BurgerTime::CreateLevel(Scene& scene)
{
	//OBSERVERS
	auto observer = std::make_shared<GameState>();

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
	std::unique_ptr<CRender> fpsCRender = std::make_unique<CRender>(fpsCounter.get(), fpsTexture);
	fpsCounter->AddComponent(std::move(fpsCRender));
	scene.Add(fpsCounter);

	CreatePlayerPawns(scene, observer);
	if(m_GameMode != "Versus") CreateNPCs(scene, observer);
	CreateTerrain(scene);
	CreateGameplayObjects(scene, observer);
}

void BurgerTime::CreatePlayerPawns(Scene& scene, std::shared_ptr<GameState> pObserver)
{
	//PAWN ONE
	const auto peterPepper = std::make_shared<GameObject>(std::string{ "Peter" });
	peterPepper->GetTransform()->SetPosition(200, 200);
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
	peterPepper->AddObserver(pObserver);
	scene.Add(peterPepper);
	m_pPlayerOnePawn = peterPepper.get();

	if (m_GameMode == "Coop")
	{
		const auto peterPepper2 = std::make_shared<GameObject>(std::string{ "Peter" });
		peterPepper2->GetTransform()->SetPosition(400, 400);
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
		peterPepper2->GetTransform()->SetPosition(400, 400);
		peterPepper2->GetTransform()->SetScale(44, 44);
		std::unique_ptr<CCollisionBox> peterCollision2 = std::make_unique<CCollisionBox>(peterPepper2.get(), CollisionGroup::Pawn);
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
		std::unique_ptr<CRender> plateCRender = std::make_unique<CRender>(plate.get(), plateTexture);
		plate->AddComponent(std::move(plateCRender));
		std::unique_ptr<CCollisionBox> plateCCollision = std::make_unique<CCollisionBox>(plate.get(), CollisionGroup::Plate);
		plate->AddComponent(std::move(plateCCollision));
		std::unique_ptr<CPlate> plateCPlate = std::make_unique<CPlate>(plate.get(), true);
		plate->AddComponent(std::move(plateCPlate));
		scene.Add(plate);
		//1//
		const auto plate1 = std::make_shared<GameObject>(std::string{ "plate" });
		plate1->GetTransform()->SetPosition(475, 475);
		plate1->GetTransform()->SetScale(160, 5);
		std::unique_ptr<CRender> plateCRender1 = std::make_unique<CRender>(plate1.get(), plateTexture);
		plate1->AddComponent(std::move(plateCRender1));
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
		std::unique_ptr<CRender> plateCRender = std::make_unique<CRender>(plate.get(), plateTexture);
		plate->AddComponent(std::move(plateCRender));
		std::unique_ptr<CCollisionBox> plateCCollision = std::make_unique<CCollisionBox>(plate.get(), CollisionGroup::Plate);
		plate->AddComponent(std::move(plateCCollision));
		std::unique_ptr<CPlate> plateCPlate = std::make_unique<CPlate>(plate.get(), true);
		plate->AddComponent(std::move(plateCPlate));
		scene.Add(plate);
		//1//
		const auto plate1 = std::make_shared<GameObject>(std::string{ "plate" });
		plate1->GetTransform()->SetPosition(475, 615);
		plate1->GetTransform()->SetScale(160, 5);
		std::unique_ptr<CRender> plateCRender1 = std::make_unique<CRender>(plate1.get(), plateTexture);
		plate1->AddComponent(std::move(plateCRender1));
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
	std::unique_ptr<CRender> plateCRender2 = std::make_unique<CRender>(plate2.get(), plateTexture);
	plate2->AddComponent(std::move(plateCRender2));
	std::unique_ptr<CCollisionBox> plateCCollision2 = std::make_unique<CCollisionBox>(plate2.get(), CollisionGroup::Plate);
	plate2->AddComponent(std::move(plateCCollision2));
	std::unique_ptr<CPlate> plateCPlate2 = std::make_unique<CPlate>(plate2.get(), true);
	plate2->AddComponent(std::move(plateCPlate2));
	scene.Add(plate2);
	//3//
	const auto plate3 = std::make_shared<GameObject>(std::string{ "plate" });
	plate3->GetTransform()->SetPosition(185, 615);
	plate3->GetTransform()->SetScale(160, 5);
	std::unique_ptr<CRender> plateCRender3 = std::make_unique<CRender>(plate3.get(), plateTexture);
	plate3->AddComponent(std::move(plateCRender3));
	std::unique_ptr<CCollisionBox> plateCCollision3 = std::make_unique<CCollisionBox>(plate3.get(), CollisionGroup::Plate);
	plate3->AddComponent(std::move(plateCCollision3));
	std::unique_ptr<CPlate> plateCPlate3 = std::make_unique<CPlate>(plate3.get(), true);
	plate3->AddComponent(std::move(plateCPlate3));
	scene.Add(plate3);
}


void BurgerTime::CreateTerrain(Scene& scene)
{

#pragma region Ladders
	//COMMON RESOURCES
	const auto ladderTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//LADDER0
	const auto ladder0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ladder0->GetTransform()->SetPosition(12, 67);
	ladder0->GetTransform()->SetScale(30, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision0 = std::make_unique<CCollisionBox>(ladder0.get(), CollisionGroup::Ladder);
	ladder0->AddComponent(std::move(ladderCCollision0));
	//std::unique_ptr<CRender> ladderCRender0 = std::make_unique<CRender>(ladder0.get(), ladderTexture, true);
	//ladder0->AddComponent(std::move(ladderCRender0));
	scene.Add(ladder0);
	//LADDER1
	const auto ladder1 = std::make_shared<GameObject>(std::string{ "Ladder1" });
	ladder1->GetTransform()->SetPosition(82, 67);
	ladder1->GetTransform()->SetScale(30, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision1 = std::make_unique<CCollisionBox>(ladder1.get(), CollisionGroup::Ladder);
	ladder1->AddComponent(std::move(ladderCCollision1));
	//std::unique_ptr<CRender> ladderCRender1 = std::make_unique<CRender>(ladder1.get(), ladderTexture, true);
	//ladder1->AddComponent(std::move(ladderCRender1));
	scene.Add(ladder1);
	//LADDER2
	const auto ladder2 = std::make_shared<GameObject>(std::string{ "Ladder2" });
	ladder2->GetTransform()->SetPosition(154, 67);
	ladder2->GetTransform()->SetScale(30, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision2 = std::make_unique<CCollisionBox>(ladder2.get(), CollisionGroup::Ladder);
	ladder2->AddComponent(std::move(ladderCCollision2));
	//std::unique_ptr<CRender> ladderCRender2 = std::make_unique<CRender>(ladder2.get(), ladderTexture, true);
	//ladder2->AddComponent(std::move(ladderCRender2));
	scene.Add(ladder2);
	//LADDER3
	const auto ladder3 = std::make_shared<GameObject>(std::string{ "Ladder3" });
	ladder3->GetTransform()->SetPosition(224, 67);
	ladder3->GetTransform()->SetScale(30, 390);
	std::unique_ptr<CCollisionBox> ladderCCollision3 = std::make_unique<CCollisionBox>(ladder3.get(), CollisionGroup::Ladder);
	ladder3->AddComponent(std::move(ladderCCollision3));
	//std::unique_ptr<CRender> ladderCRender3 = std::make_unique<CRender>(ladder3.get(), ladderTexture, true);
	//ladder3->AddComponent(std::move(ladderCRender3));
	scene.Add(ladder3);
	//LADDER4
	const auto ladder4 = std::make_shared<GameObject>(std::string{ "Ladder4" });
	ladder4->GetTransform()->SetPosition(295, 67);
	ladder4->GetTransform()->SetScale(30, 475);
	std::unique_ptr<CCollisionBox> ladderCCollision4 = std::make_unique<CCollisionBox>(ladder4.get(), CollisionGroup::Ladder);
	ladder4->AddComponent(std::move(ladderCCollision4));
	//std::unique_ptr<CRender> ladderCRender4 = std::make_unique<CRender>(ladder4.get(), ladderTexture, true);
	//ladder4->AddComponent(std::move(ladderCRender4));
	scene.Add(ladder4);
	//LADDER5
	const auto ladder5 = std::make_shared<GameObject>(std::string{ "Ladder5" });
	ladder5->GetTransform()->SetPosition(366, 67);
	ladder5->GetTransform()->SetScale(30, 390);
	std::unique_ptr<CCollisionBox> ladderCCollision5 = std::make_unique<CCollisionBox>(ladder5.get(), CollisionGroup::Ladder);
	ladder5->AddComponent(std::move(ladderCCollision5));
	//std::unique_ptr<CRender> ladderCRender5 = std::make_unique<CRender>(ladder5.get(), ladderTexture, true);
	//ladder5->AddComponent(std::move(ladderCRender5));
	scene.Add(ladder5);
	//LADDER6
	const auto ladder6 = std::make_shared<GameObject>(std::string{ "Ladder6" });
	ladder6->GetTransform()->SetPosition(436, 67);
	ladder6->GetTransform()->SetScale(30, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision6 = std::make_unique<CCollisionBox>(ladder6.get(), CollisionGroup::Ladder);
	ladder6->AddComponent(std::move(ladderCCollision6));
	//std::unique_ptr<CRender> ladderCRender6 = std::make_unique<CRender>(ladder6.get(), ladderTexture, true);
	//ladder6->AddComponent(std::move(ladderCRender6));
	scene.Add(ladder6);
	//LADDER7
	const auto ladder7 = std::make_shared<GameObject>(std::string{ "Ladder7" });
	ladder7->GetTransform()->SetPosition(508, 67);
	ladder7->GetTransform()->SetScale(30, 200);
	std::unique_ptr<CCollisionBox> ladderCCollision7 = std::make_unique<CCollisionBox>(ladder7.get(), CollisionGroup::Ladder);
	ladder7->AddComponent(std::move(ladderCCollision7));
	//std::unique_ptr<CRender> ladderCRender7 = std::make_unique<CRender>(ladder7.get(), ladderTexture, true);
	//ladder7->AddComponent(std::move(ladderCRender7));
	scene.Add(ladder7);
	//LADDER8
	const auto ladder8 = std::make_shared<GameObject>(std::string{ "Ladder8" });
	ladder8->GetTransform()->SetPosition(578, 67);
	ladder8->GetTransform()->SetScale(30, 200);
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
	ground0->GetTransform()->SetScale(630, 6);
	std::unique_ptr<CCollisionBox> groundCCollision0 = std::make_unique<CCollisionBox>(ground0.get(), CollisionGroup::Ground);
	ground0->AddComponent(std::move(groundCCollision0));
	//std::unique_ptr<CRender> groundCTexture0 = std::make_unique<CRender>(ground0.get(), groundTexture, true);
	//ground0->AddComponent(std::move(groundCTexture0));
	scene.Add(ground0);
	//GROUND1
	const auto ground1 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground1->GetTransform()->SetPosition(0, 115);
	ground1->GetTransform()->SetScale(340, 6);
	std::unique_ptr<CCollisionBox> groundCCollision1 = std::make_unique<CCollisionBox>(ground1.get(), CollisionGroup::Ground);
	ground1->AddComponent(std::move(groundCCollision1));
	//std::unique_ptr<CRender> groundCTexture1 = std::make_unique<CRender>(ground1.get(), groundTexture, true);
	//ground1->AddComponent(std::move(groundCTexture1));
	scene.Add(ground1);
	//GROUND2
	const auto ground2 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground2->GetTransform()->SetPosition(0, 162);
	ground2->GetTransform()->SetScale(190, 6);
	std::unique_ptr<CCollisionBox> groundCCollision2 = std::make_unique<CCollisionBox>(ground2.get(), CollisionGroup::Ground);
	ground2->AddComponent(std::move(groundCCollision2));
	//std::unique_ptr<CRender> groundCTexture2 = std::make_unique<CRender>(ground2.get(), groundTexture, true);
	//ground2->AddComponent(std::move(groundCTexture2));
	scene.Add(ground2);
	//GROUND3
	const auto ground3 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground3->GetTransform()->SetPosition(287, 162);
	ground3->GetTransform()->SetScale(331, 6);
	std::unique_ptr<CCollisionBox> groundCCollision3 = std::make_unique<CCollisionBox>(ground3.get(), CollisionGroup::Ground);
	ground3->AddComponent(std::move(groundCCollision3));
	//std::unique_ptr<CRender> groundCTexture3 = std::make_unique<CRender>(ground3.get(), groundTexture, true);
	//ground3->AddComponent(std::move(groundCTexture3));
	scene.Add(ground3);
	//GROUND4
	const auto ground4 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground4->GetTransform()->SetPosition(147, 210);
	ground4->GetTransform()->SetScale(200, 6);
	std::unique_ptr<CCollisionBox> groundCCollision4 = std::make_unique<CCollisionBox>(ground4.get(), CollisionGroup::Ground);
	ground4->AddComponent(std::move(groundCCollision4));
	//std::unique_ptr<CRender> groundCTexture4 = std::make_unique<CRender>(ground4.get(), groundTexture, true);
	//ground4->AddComponent(std::move(groundCTexture4));
	scene.Add(ground4);
	//GROUND5
	const auto ground5 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground5->GetTransform()->SetPosition(363, 210);
	ground5->GetTransform()->SetScale(253, 6);
	std::unique_ptr<CCollisionBox> groundCCollision5 = std::make_unique<CCollisionBox>(ground5.get(), CollisionGroup::Ground);
	ground5->AddComponent(std::move(groundCCollision5));
	//std::unique_ptr<CRender> groundCTexture5 = std::make_unique<CRender>(ground5.get(), groundTexture, true);
	//ground5->AddComponent(std::move(groundCTexture5));
	scene.Add(ground5);
	//GROUND6
	const auto ground6 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground6->GetTransform()->SetPosition(0, 257);
	ground6->GetTransform()->SetScale(630, 7);
	std::unique_ptr<CCollisionBox> groundCCollision6 = std::make_unique<CCollisionBox>(ground6.get(), CollisionGroup::Ground);
	ground6->AddComponent(std::move(groundCCollision6));
	//std::unique_ptr<CRender> groundCTexture6 = std::make_unique<CRender>(ground6.get(), groundTexture, true);
	//ground6->AddComponent(std::move(groundCTexture6));
	scene.Add(ground6);
	//GROUND7
	const auto ground7 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground7->GetTransform()->SetPosition(287, 304);
	ground7->GetTransform()->SetScale(200, 6);
	std::unique_ptr<CCollisionBox> groundCCollision7 = std::make_unique<CCollisionBox>(ground7.get(), CollisionGroup::Ground);
	ground7->AddComponent(std::move(groundCCollision7));
	//std::unique_ptr<CRender> groundCTexture7 = std::make_unique<CRender>(ground7.get(), groundTexture, true);
	//ground7->AddComponent(std::move(groundCTexture7));
	scene.Add(ground7);
	//GROUND8
	const auto ground8 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground8->GetTransform()->SetPosition(147, 351);
	ground8->GetTransform()->SetScale(200, 6);
	std::unique_ptr<CCollisionBox> groundCCollision8 = std::make_unique<CCollisionBox>(ground8.get(), CollisionGroup::Ground);
	ground8->AddComponent(std::move(groundCCollision8));
	//std::unique_ptr<CRender> groundCTexture8 = std::make_unique<CRender>(ground8.get(), groundTexture, true);
	//ground8->AddComponent(std::move(groundCTexture8));
	scene.Add(ground8);
	//GROUND9
	const auto ground9 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground9->GetTransform()->SetPosition(287, 399);
	ground9->GetTransform()->SetScale(200, 6);
	std::unique_ptr<CCollisionBox> groundCCollision9 = std::make_unique<CCollisionBox>(ground9.get(), CollisionGroup::Ground);
	ground9->AddComponent(std::move(groundCCollision9));
	//std::unique_ptr<CRender> groundCTexture9 = std::make_unique<CRender>(ground9.get(), groundTexture, true);
	//ground9->AddComponent(std::move(groundCTexture9));
	scene.Add(ground9);
	//GROUND10
	const auto ground10 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground10->GetTransform()->SetPosition(146, 446);
	ground10->GetTransform()->SetScale(331, 6);
	std::unique_ptr<CCollisionBox> groundCCollision10 = std::make_unique<CCollisionBox>(ground10.get(), CollisionGroup::Ground);
	ground10->AddComponent(std::move(groundCCollision10));
	//std::unique_ptr<CRender> groundCTexture10 = std::make_unique<CRender>(ground10.get(), groundTexture, true);
	//ground10->AddComponent(std::move(groundCTexture10));
	scene.Add(ground10);
	//GROUND11
	const auto ground11 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground11->GetTransform()->SetPosition(287, 541);
	ground11->GetTransform()->SetScale(45, 6);
	std::unique_ptr<CCollisionBox> groundCCollision11 = std::make_unique<CCollisionBox>(ground11.get(), CollisionGroup::Ground);
	ground11->AddComponent(std::move(groundCCollision11));
	//std::unique_ptr<CRender> groundCTexture11 = std::make_unique<CRender>(ground11.get(), groundTexture, true);
	//ground11->AddComponent(std::move(groundCTexture11));
	scene.Add(ground11);
#pragma endregion Ground
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

	return inputManagers;
}