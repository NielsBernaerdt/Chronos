#include "BurgerTime.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

#include "CollisionGroups.h"
#include "InputManager.h"
#include "InputCommands.h"
#include "BCommand.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
//components
#include "CPoints.h"
#include "CFPS.h"
#include "CHealth.h"
#include "CRender.h"
#include "CText.h"
#include "CTransform.h"
//Observers
#include "Achievements.h"
#include "CBurgerIngredient.h"
#include "CCollisionBox.h"
#include "CPeterPepper.h"

//OWN SCENES//
void BurgerTime::SandboxScene(Scene& scene)
{	//Background image
	const auto background = std::make_shared<GameObject>(std::string{ "Background" });
	background->GetTransform()->SetScale(1280, 720);
	auto bgTexture = ResourceManager::GetInstance().LoadTexture("level0.png");
	const auto bgCRender = std::make_shared<CRender>(background.get(), bgTexture, true);
	background->AddComponent(bgCRender);
	scene.Add(background);

	//Make FPS object
	const auto fpsCounter = std::make_shared<GameObject>(std::string{ "FPSCounter" });
	const auto fpsCText = std::make_shared<CText>(fpsCounter.get(), "FPS Counter", 36);
	fpsCounter->AddComponent(fpsCText);
	const auto fpsComp = std::make_shared<CFPS>(fpsCounter.get());
	fpsCounter->AddComponent(fpsComp);
	auto fpsTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto fpsCRender = std::make_shared<CRender>(fpsCounter.get(), fpsTexture);
	fpsCounter->AddComponent(fpsCRender);
	scene.Add(fpsCounter);

	//LADDER
	const auto ladder = std::make_shared<GameObject>(std::string{ "Ladder" });
	ladder->GetTransform()->SetPosition(50, 240);
	ladder->GetTransform()->SetScale(50, 200);
	const auto ladderCCollision = std::make_shared<CCollisionBox>(ladder.get(), CollisionGroup::Ladder);
	ladder->AddComponent(ladderCCollision);
	const auto ladderTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto ladderCRender = std::make_shared<CRender>(ladder.get(), ladderTexture, true);
	ladder->AddComponent(ladderCRender);
	scene.Add(ladder);

	//GROUND
	const auto ground = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground->GetTransform()->SetPosition(0, 240);
	ground->GetTransform()->SetScale(1280, 10);
	const auto groundCCollision = std::make_shared<CCollisionBox>(ground.get(), CollisionGroup::Ground);
	ground->AddComponent(groundCCollision);
	const auto groundTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto groundCTexture = std::make_shared<CRender>(ground.get(), groundTexture, true);
	ground->AddComponent(groundCTexture);
	scene.Add(ground);

	//PATTY 0
	const auto pattyParent = std::make_shared<GameObject>(std::string{ "PattyOne" });
	pattyParent->GetTransform()->SetPosition(95, 500);
	//COMMON RESOURCES
	const auto pattyTexture = ResourceManager::GetInstance().LoadTexture("BurgerIngredients.png");
	//PATTY 0.0
	const auto pattyChild0 = std::make_shared<GameObject>(std::string{ "PattyOneChildZero" });
	pattyChild0->GetTransform()->SetScale(50, 50);

	const auto pattyChild0Collision = std::make_shared<CCollisionBox>(pattyChild0.get(), CollisionGroup::Burger);
	pattyChild0->AddComponent(pattyChild0Collision);

	const auto pattyCRender = std::make_shared<CRender>(pattyChild0.get(), pattyTexture, true);
	pattyChild0->AddComponent(pattyCRender);
	const auto pattyCBurgerIngredient = std::make_shared<CBurgerIngredient>(pattyChild0.get(), Ingredient::Cheese, 0);
	pattyChild0->AddComponent(pattyCBurgerIngredient);
	scene.Add(pattyChild0);
	pattyChild0->SetParent(pattyParent);
	//PATTY 0.1
	const auto pattyChild1 = std::make_shared<GameObject>(std::string{ "PattyOneChildOne" });
	pattyChild1->GetTransform()->SetScale(50, 50);

	const auto pattyChild1Collision = std::make_shared<CCollisionBox>(pattyChild1.get(), CollisionGroup::Burger);
	pattyChild1->AddComponent(pattyChild1Collision);

	const auto pattyCRender1 = std::make_shared<CRender>(pattyChild1.get(), pattyTexture, true);
	pattyChild1->AddComponent(pattyCRender1);
	const auto pattyCBurgerIngredient1 = std::make_shared<CBurgerIngredient>(pattyChild1.get(), Ingredient::Cheese, 1);
	pattyChild1->AddComponent(pattyCBurgerIngredient1);
	scene.Add(pattyChild1);
	pattyChild1->SetParent(pattyParent);
	//PATTY 0.2
	const auto pattyChild2 = std::make_shared<GameObject>(std::string{ "PattyChildTwo" });
	pattyChild2->GetTransform()->SetScale(50, 50);

	const auto pattyChild2Collision = std::make_shared<CCollisionBox>(pattyChild2.get(), CollisionGroup::Burger);
	pattyChild2->AddComponent(pattyChild2Collision);

	const auto pattyCRender2 = std::make_shared<CRender>(pattyChild2.get(), pattyTexture, true);
	pattyChild2->AddComponent(pattyCRender2);
	const auto pattyCBurgerIngredient2 = std::make_shared<CBurgerIngredient>(pattyChild2.get(), Ingredient::Cheese, 2);
	pattyChild2->AddComponent(pattyCBurgerIngredient2);
	scene.Add(pattyChild2);
	pattyChild2->SetParent(pattyParent);
	//PATTY 0.3
	const auto pattyChild3 = std::make_shared<GameObject>(std::string{ "PattyOneChildThree" });
	pattyChild3->GetTransform()->SetScale(50, 50);

	const auto pattyChild3Collision = std::make_shared<CCollisionBox>(pattyChild3.get(), CollisionGroup::Burger);
	pattyChild3->AddComponent(pattyChild3Collision);

	const auto pattyCRender3 = std::make_shared<CRender>(pattyChild3.get(), pattyTexture, true);
	pattyChild3->AddComponent(pattyCRender3);
	const auto pattyCBurgerIngredient3 = std::make_shared<CBurgerIngredient>(pattyChild3.get(), Ingredient::Cheese, 3);
	pattyChild3->AddComponent(pattyCBurgerIngredient3);
	scene.Add(pattyChild3);
	pattyChild3->SetParent(pattyParent);

	//PAWN
	const auto peterPepper = std::make_shared<GameObject>(std::string{ "Peter" });
	peterPepper->GetTransform()->SetPosition(200, 200);

	const auto peterCollision = std::make_shared<CCollisionBox>(peterPepper.get(), CollisionGroup::Pawn);
	peterPepper->AddComponent(peterCollision);

	const auto peterTexture = ResourceManager::GetInstance().LoadTexture("PeterSprites.png");
	const auto peterCRender = std::make_shared<CRender>(peterPepper.get(), peterTexture, true);
	peterPepper->AddComponent(peterCRender);
	const auto peterCPeterPepper = std::make_shared<CPeterPepper>(peterPepper.get());
	peterPepper->AddComponent(peterCPeterPepper);
	scene.Add(peterPepper);

	m_pPlayerPawn = peterPepper.get();

}
void BurgerTime::SceneGraphTestScene(Scene& scene) const
{
	const std::shared_ptr<GameObject> parentObject = std::make_shared<GameObject>("Parent");
	parentObject->GetTransform()->SetPosition(200, 0);
	scene.Add(parentObject);

	const std::shared_ptr<GameObject> secondParentObject = std::make_shared<GameObject>("ParentTWO");
	secondParentObject->GetTransform()->SetPosition(0, 200);
	scene.Add(secondParentObject);

	const std::shared_ptr<GameObject> childObject = std::make_shared<GameObject>("Child");
	childObject->GetTransform()->SetPosition(500, 0);
	auto logoTexture = ResourceManager::GetInstance().LoadTexture("logo.png");
	const auto logoCRender = std::make_shared<CRender>(childObject.get(), logoTexture);
	childObject->AddComponent(logoCRender);
	scene.Add(childObject);

	childObject->SetParent(parentObject);
	parentObject->SetParent(secondParentObject);

	//todo Cant fix parent at runtime
	//childObject->SetParent(secondParentObject);
	//childObject->GetTransform()->UpdateRelativeTransform();

	//logoCRender->UpdateRelativeTransform();
}
void BurgerTime::ObserverScene(Scene& scene) const
{
	//Achievements Observer
	std::shared_ptr<Achievements> achievements = std::make_shared<Achievements>();

	// PlayerObject
	auto peterPawn = std::make_shared<GameObject>(std::string{"PawnObject"});
		//HealthComponent
		std::shared_ptr<CHealth> pawnCHealth = std::make_shared<CHealth>(peterPawn.get());
		pawnCHealth->SetHealth(3);
		//PointsComponent
		std::shared_ptr<CPoints> pawnCPoints = std::make_shared<CPoints>(peterPawn.get());

	peterPawn->AddComponent(pawnCHealth);
	peterPawn->AddComponent(pawnCPoints);

	peterPawn->AddObserver(achievements.get());

	scene.Add(peterPawn);

	///
	std::cout << "Current HP: " << pawnCHealth->GetHealth() << std::endl;
	std::cout << "Current Points: " << pawnCPoints->GetPoints() << std::endl;
	pawnCHealth->SetHealth(1);
	std::cout << "First Reduction to 1HP: " << pawnCHealth->GetHealth() << std::endl;
	std::cout << "Current Points: " << pawnCPoints->GetPoints() << std::endl;
	pawnCHealth->SetHealth(0);
	std::cout << "Second Reduction to 0HP: " << pawnCHealth->GetHealth() << std::endl;
	std::cout << "Current Points: " << pawnCPoints->GetPoints() << std::endl;
}

void BurgerTime::ConfigureInput(InputManager* input)
{
	input->BindCommandToButton(ControllerButton::DPadRight, std::make_unique<MoveRight>());
	input->BindCommandToButton(ControllerButton::DPadLeft, std::make_unique<MoveLeft>());
	input->BindCommandToButton(ControllerButton::DPadUp, std::make_unique<ClimbUp>());
	input->BindCommandToButton(ControllerButton::DPadDown, std::make_unique<ClimbDown>());

	input->SetPawn(m_pPlayerPawn);
}