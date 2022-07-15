#include "Tron.h"
#include <InputManager.h>
#include <GameObject.h>
#include <ResourceManager.h>
#include <CRender.h>
#include <Scene.h>
#include <SDL_mouse.h>
#include <SDL_scancode.h>

#include "CBullet.h"
#include "CCollisionBox.h"
#include "CollisionGroups.h"
#include "CTankTron.h"
#include "InputCommands.h"


bool Tron::ReadFromFile()
{
	//READ FILE, RETURN TRUE IF INVALID
	CreateScenes();
	return false;
}

void Tron::CreateScenes()
{
	CreateScene0();
	CreateScene1();
	CreateScene2();
}

void Tron::CreateScene0()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level0");
	scene.SetActive(true);
#pragma region PlayerPawn
	const auto tronTank = std::make_shared<GameObject>(std::string{ "TronPawnOne" });
	tronTank->GetTransform()->SetPosition(0, 90);
	tronTank->GetTransform()->SetScale(44, 44);

	const auto tronTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankRed.png");
	std::unique_ptr<CRender> tronCRender = std::make_unique<CRender>(tronTank.get(), tronTexture, true);
	tronTank->AddComponent(std::move(tronCRender));

	std::unique_ptr<CTankTron> tronCTankTron = std::make_unique<CTankTron>(tronTank.get());
	tronTank->AddComponent(std::move(tronCTankTron));

	std::unique_ptr<CCollisionBox> tronCCollision = std::make_unique<CCollisionBox>(tronTank.get(), CollisionGroup::Pawn);
	tronTank->AddComponent(std::move(tronCCollision));

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
#pragma endregion PlayerPawn

#pragma region GameplayObjects
	const auto bullet = std::make_shared<GameObject>(std::string{ "bullet" });
	bullet->GetTransform()->SetPosition(150, 150);
	bullet->GetTransform()->SetScale(20, 20);

	const auto bulletTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> bulletCRender = std::make_unique<CRender>(bullet.get(), bulletTexture, true);
	bullet->AddComponent(std::move(bulletCRender));

	std::unique_ptr<CCollisionBox> bulletCCollision = std::make_unique<CCollisionBox>(bullet.get(), CollisionGroup::Wall);
	bullet->AddComponent(std::move(bulletCCollision));

	std::unique_ptr<CBullet> bulletCBullet = std::make_unique<CBullet>(bullet.get(), glm::vec3{100, 100, 0});
	bullet->AddComponent(std::move(bulletCBullet));

	scene.Add(bullet);
#pragma endregion GameplayObjects

#pragma region Terrain
	const auto wallTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//1//
	const auto wall = std::make_shared<GameObject>(std::string{ "WallOne" });
	//CTRANSFORM
	wall->GetTransform()->SetPosition(100, 100);
	wall->GetTransform()->SetScale(300, 30);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender = std::make_unique<CRender>(wall.get(), wallTexture, true);
	wall->AddComponent(std::move(wallCRender));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision = std::make_unique<CCollisionBox>(wall.get(), CollisionGroup::Wall);
	wall->AddComponent(std::move(wallCCollision));
	scene.Add(wall);
	//2//
	const auto wall2 = std::make_shared<GameObject>(std::string{ "WallOne" });
	//CTRANSFORM
	wall2->GetTransform()->SetPosition(400, 100);
	wall2->GetTransform()->SetScale(30, 300);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender2 = std::make_unique<CRender>(wall2.get(), wallTexture, true);
	wall2->AddComponent(std::move(wallCRender2));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision2 = std::make_unique<CCollisionBox>(wall2.get(), CollisionGroup::Wall);
	wall2->AddComponent(std::move(wallCCollision2));
	scene.Add(wall2);
	//3//
	const auto wall3 = std::make_shared<GameObject>(std::string{ "WallOne" });
	//CTRANSFORM
	wall3->GetTransform()->SetPosition(100, 400);
	wall3->GetTransform()->SetScale(300, 30);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender3 = std::make_unique<CRender>(wall3.get(), wallTexture, true);
	wall3->AddComponent(std::move(wallCRender3));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision3 = std::make_unique<CCollisionBox>(wall3.get(), CollisionGroup::Wall);
	wall3->AddComponent(std::move(wallCCollision3));
	scene.Add(wall3);
	//4//
	const auto wall4 = std::make_shared<GameObject>(std::string{ "WallOne" });
	//CTRANSFORM
	wall4->GetTransform()->SetPosition(100, 100);
	wall4->GetTransform()->SetScale(30, 300);
	//TEX + CRENDER
	std::unique_ptr<CRender> wallCRender4 = std::make_unique<CRender>(wall4.get(), wallTexture, true);
	wall4->AddComponent(std::move(wallCRender4));
	//CCOLLISION
	std::unique_ptr<CCollisionBox> wallCCollision4 = std::make_unique<CCollisionBox>(wall4.get(), CollisionGroup::Wall);
	wall4->AddComponent(std::move(wallCCollision4));
	scene.Add(wall4);
#pragma endregion Terrain
}

void Tron::CreateScene1()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level1");
	//scene.SetActive(true);

	const auto tronTank = std::make_shared<GameObject>(std::string{ "TronPawnOne" });
	tronTank->GetTransform()->SetPosition(300, 90);
	tronTank->GetTransform()->SetScale(44, 44);

	const auto tronTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankRed.png");
	std::unique_ptr<CRender> tronCRender = std::make_unique<CRender>(tronTank.get(), tronTexture, true);
	tronTank->AddComponent(std::move(tronCRender));

	std::unique_ptr<CTankTron> tronCTankTron = std::make_unique<CTankTron>(tronTank.get());
	tronTank->AddComponent(std::move(tronCTankTron));

	std::unique_ptr<CCollisionBox> tronCCollision = std::make_unique<CCollisionBox>(tronTank.get(), CollisionGroup::Pawn);
	tronTank->AddComponent(std::move(tronCCollision));

	scene.Add(tronTank);

	/////////////////TANKBARREL////////////////////
	const auto tronTankBarrel = std::make_shared<GameObject>(std::string{ "TronPawnOneBarrel" });
	tronTankBarrel->GetTransform()->SetPosition(22, 22);
	tronTankBarrel->GetTransform()->SetScale(40, 10);

	const auto tronBarrelTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> tronBarrelCRender = std::make_unique<CRender>(tronTankBarrel.get(), tronBarrelTexture, true);
	tronTankBarrel->AddComponent(std::move(tronBarrelCRender));

	scene.Add(tronTankBarrel);

	tronTankBarrel->SetParent(tronTank.get());

	//m_pPlayerOnePawn = tronTank.get();
}

void Tron::CreateScene2()
{
	auto& scene = SceneManager::GetInstance().CreateScene("Level2");

	const auto tronTank = std::make_shared<GameObject>(std::string{ "TronPawnOne" });
	tronTank->GetTransform()->SetPosition(500, 90);
	tronTank->GetTransform()->SetScale(44, 44);

	const auto tronTexture = ResourceManager::GetInstance().LoadTexture("Tron/TankRed.png");
	std::unique_ptr<CRender> tronCRender = std::make_unique<CRender>(tronTank.get(), tronTexture, true);
	tronTank->AddComponent(std::move(tronCRender));

	std::unique_ptr<CTankTron> tronCTankTron = std::make_unique<CTankTron>(tronTank.get());
	tronTank->AddComponent(std::move(tronCTankTron));

	std::unique_ptr<CCollisionBox> tronCCollision = std::make_unique<CCollisionBox>(tronTank.get(), CollisionGroup::Pawn);
	tronTank->AddComponent(std::move(tronCCollision));

	scene.Add(tronTank);

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

InputManager* Tron::ConfigureInput()
{
	InputManager* inputManager = new InputManager{};

	//INPUT PAWN ONE
	// GAMEPAD
	inputManager->BindCommandToButton(ControllerButton::DPadRight, std::make_unique<MoveHorizontal>(true));
	inputManager->BindCommandToButton(ControllerButton::DPadLeft, std::make_unique<MoveHorizontal>(false));
	inputManager->BindCommandToButton(ControllerButton::DPadUp, std::make_unique<MoveVertical>(true));
	inputManager->BindCommandToButton(ControllerButton::DPadDown, std::make_unique<MoveVertical>(false));
	inputManager->AddController(0, m_pPlayerOnePawn);
	//KEYBOARD|MOUSE
	inputManager->BindCommandToButton(SDL_SCANCODE_D, std::make_unique<MoveHorizontal>(true));
	inputManager->BindCommandToButton(SDL_SCANCODE_A, std::make_unique<MoveHorizontal>(false));
	inputManager->BindCommandToButton(SDL_SCANCODE_W, std::make_unique<MoveVertical>(true));
	inputManager->BindCommandToButton(SDL_SCANCODE_S, std::make_unique<MoveVertical>(false));
	inputManager->BindCommandToButton(SDL_BUTTON_LMASK, std::make_unique<Shoot>(), true);
	inputManager->AddController(4, m_pPlayerOnePawn);

	return inputManager;
}