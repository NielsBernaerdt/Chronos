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
#include "CPlate.h"

//OWN SCENES//
void BurgerTime::SandboxScene(Scene& scene)
{	//Background image
	const auto background = std::make_shared<GameObject>(std::string{ "Background" });
	background->GetTransform()->SetScale(620, 620);
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

#pragma region Ladders
	//COMMON RESOURCES
	const auto ladderTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//LADDER0
	const auto ladder0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ladder0->GetTransform()->SetPosition(12, 67);
	ladder0->GetTransform()->SetScale(30, 200);
	const auto ladderCCollision0 = std::make_shared<CCollisionBox>(ladder0.get(), CollisionGroup::Ladder);
	ladder0->AddComponent(ladderCCollision0);
	const auto ladderCRender0 = std::make_shared<CRender>(ladder0.get(), ladderTexture, true);
	ladder0->AddComponent(ladderCRender0);
	scene.Add(ladder0);
	//LADDER1
	const auto ladder1 = std::make_shared<GameObject>(std::string{ "Ladder1" });
	ladder1->GetTransform()->SetPosition(82, 67);
	ladder1->GetTransform()->SetScale(30, 200);
	const auto ladderCCollision1 = std::make_shared<CCollisionBox>(ladder1.get(), CollisionGroup::Ladder);
	ladder1->AddComponent(ladderCCollision1);
	const auto ladderCRender1 = std::make_shared<CRender>(ladder1.get(), ladderTexture, true);
	ladder1->AddComponent(ladderCRender1);
	scene.Add(ladder1);
	//LADDER2
	const auto ladder2 = std::make_shared<GameObject>(std::string{ "Ladder2" });
	ladder2->GetTransform()->SetPosition(154, 67);
	ladder2->GetTransform()->SetScale(30, 200);
	const auto ladderCCollision2 = std::make_shared<CCollisionBox>(ladder2.get(), CollisionGroup::Ladder);
	ladder2->AddComponent(ladderCCollision2);
	const auto ladderCRender2 = std::make_shared<CRender>(ladder2.get(), ladderTexture, true);
	ladder2->AddComponent(ladderCRender2);
	scene.Add(ladder2);
	//LADDER3
	const auto ladder3 = std::make_shared<GameObject>(std::string{ "Ladder3" });
	ladder3->GetTransform()->SetPosition(224, 67);
	ladder3->GetTransform()->SetScale(30, 390);
	const auto ladderCCollision3 = std::make_shared<CCollisionBox>(ladder3.get(), CollisionGroup::Ladder);
	ladder3->AddComponent(ladderCCollision3);
	const auto ladderCRender3 = std::make_shared<CRender>(ladder3.get(), ladderTexture, true);
	ladder3->AddComponent(ladderCRender3);
	scene.Add(ladder3);
	//LADDER4
	const auto ladder4 = std::make_shared<GameObject>(std::string{ "Ladder4" });
	ladder4->GetTransform()->SetPosition(295, 67);
	ladder4->GetTransform()->SetScale(30, 475);
	const auto ladderCCollision4 = std::make_shared<CCollisionBox>(ladder4.get(), CollisionGroup::Ladder);
	ladder4->AddComponent(ladderCCollision4);
	const auto ladderCRender4 = std::make_shared<CRender>(ladder4.get(), ladderTexture, true);
	ladder4->AddComponent(ladderCRender4);
	scene.Add(ladder4);
	//LADDER5
	const auto ladder5 = std::make_shared<GameObject>(std::string{ "Ladder5" });
	ladder5->GetTransform()->SetPosition(366, 67);
	ladder5->GetTransform()->SetScale(30, 390);
	const auto ladderCCollision5 = std::make_shared<CCollisionBox>(ladder5.get(), CollisionGroup::Ladder);
	ladder5->AddComponent(ladderCCollision5);
	const auto ladderCRender5 = std::make_shared<CRender>(ladder5.get(), ladderTexture, true);
	ladder5->AddComponent(ladderCRender5);
	scene.Add(ladder5);
	//LADDER6
	const auto ladder6 = std::make_shared<GameObject>(std::string{ "Ladder6" });
	ladder6->GetTransform()->SetPosition(436, 67);
	ladder6->GetTransform()->SetScale(30, 200);
	const auto ladderCCollision6 = std::make_shared<CCollisionBox>(ladder6.get(), CollisionGroup::Ladder);
	ladder6->AddComponent(ladderCCollision6);
	const auto ladderCRender6 = std::make_shared<CRender>(ladder6.get(), ladderTexture, true);
	ladder6->AddComponent(ladderCRender6);
	scene.Add(ladder6);
	//LADDER7
	const auto ladder7 = std::make_shared<GameObject>(std::string{ "Ladder7" });
	ladder7->GetTransform()->SetPosition(508, 67);
	ladder7->GetTransform()->SetScale(30, 200);
	const auto ladderCCollision7 = std::make_shared<CCollisionBox>(ladder7.get(), CollisionGroup::Ladder);
	ladder7->AddComponent(ladderCCollision7);
	const auto ladderCRender7 = std::make_shared<CRender>(ladder7.get(), ladderTexture, true);
	ladder7->AddComponent(ladderCRender7);
	scene.Add(ladder7);
	//LADDER8
	const auto ladder8 = std::make_shared<GameObject>(std::string{ "Ladder8" });
	ladder8->GetTransform()->SetPosition(578, 67);
	ladder8->GetTransform()->SetScale(30, 200);
	const auto ladderCCollision8 = std::make_shared<CCollisionBox>(ladder8.get(), CollisionGroup::Ladder);
	ladder8->AddComponent(ladderCCollision8);
	const auto ladderCRender8 = std::make_shared<CRender>(ladder8.get(), ladderTexture, true);
	ladder8->AddComponent(ladderCRender8);
	scene.Add(ladder8);
#pragma endregion Ladders

#pragma region Ground
	//COMMON RESOURCES
	const auto groundTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	//GROUND0
	const auto ground0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground0->GetTransform()->SetPosition(0, 68);
	ground0->GetTransform()->SetScale(630, 6);
	const auto groundCCollision0 = std::make_shared<CCollisionBox>(ground0.get(), CollisionGroup::Ground);
	ground0->AddComponent(groundCCollision0);
	const auto groundCTexture0 = std::make_shared<CRender>(ground0.get(), groundTexture, true);
	ground0->AddComponent(groundCTexture0);
	scene.Add(ground0);
	//GROUND1
	const auto ground1 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground1->GetTransform()->SetPosition(0, 115);
	ground1->GetTransform()->SetScale(340, 6);
	const auto groundCCollision1 = std::make_shared<CCollisionBox>(ground1.get(), CollisionGroup::Ground);
	ground1->AddComponent(groundCCollision1);
	const auto groundCTexture1 = std::make_shared<CRender>(ground1.get(), groundTexture, true);
	ground1->AddComponent(groundCTexture1);
	scene.Add(ground1);
	//GROUND2
	const auto ground2 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground2->GetTransform()->SetPosition(0, 162);
	ground2->GetTransform()->SetScale(190, 6);
	const auto groundCCollision2 = std::make_shared<CCollisionBox>(ground2.get(), CollisionGroup::Ground);
	ground2->AddComponent(groundCCollision2);
	const auto groundCTexture2 = std::make_shared<CRender>(ground2.get(), groundTexture, true);
	ground2->AddComponent(groundCTexture2);
	scene.Add(ground2);
	//GROUND3
	const auto ground3 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground3->GetTransform()->SetPosition(287, 162);
	ground3->GetTransform()->SetScale(331, 6);
	const auto groundCCollision3 = std::make_shared<CCollisionBox>(ground3.get(), CollisionGroup::Ground);
	ground3->AddComponent(groundCCollision3);
	const auto groundCTexture3 = std::make_shared<CRender>(ground3.get(), groundTexture, true);
	ground3->AddComponent(groundCTexture3);
	scene.Add(ground3);
	//GROUND4
	const auto ground4 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground4->GetTransform()->SetPosition(147, 210);
	ground4->GetTransform()->SetScale(200, 6);
	const auto groundCCollision4 = std::make_shared<CCollisionBox>(ground4.get(), CollisionGroup::Ground);
	ground4->AddComponent(groundCCollision4);
	const auto groundCTexture4 = std::make_shared<CRender>(ground4.get(), groundTexture, true);
	ground4->AddComponent(groundCTexture4);
	scene.Add(ground4);
	//GROUND5
	const auto ground5 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground5->GetTransform()->SetPosition(363, 210);
	ground5->GetTransform()->SetScale(253, 6);
	const auto groundCCollision5 = std::make_shared<CCollisionBox>(ground5.get(), CollisionGroup::Ground);
	ground5->AddComponent(groundCCollision5);
	const auto groundCTexture5 = std::make_shared<CRender>(ground5.get(), groundTexture, true);
	ground5->AddComponent(groundCTexture5);
	scene.Add(ground5);
	//GROUND6
	const auto ground6 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground6->GetTransform()->SetPosition(0, 257);
	ground6->GetTransform()->SetScale(630, 7);
	const auto groundCCollisio6 = std::make_shared<CCollisionBox>(ground6.get(), CollisionGroup::Ground);
	ground6->AddComponent(groundCCollisio6);
	const auto groundCTextur6 = std::make_shared<CRender>(ground6.get(), groundTexture, true);
	ground6->AddComponent(groundCTextur6);
	scene.Add(ground6);
	//GROUND7
	const auto ground7 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground7->GetTransform()->SetPosition(287, 304);
	ground7->GetTransform()->SetScale(200, 6);
	const auto groundCCollision7 = std::make_shared<CCollisionBox>(ground7.get(), CollisionGroup::Ground);
	ground7->AddComponent(groundCCollision7);
	const auto groundCTexture7 = std::make_shared<CRender>(ground7.get(), groundTexture, true);
	ground7->AddComponent(groundCTexture7);
	scene.Add(ground7);
	//GROUND8
	const auto groun8 = std::make_shared<GameObject>(std::string{ "Ladder" });
	groun8->GetTransform()->SetPosition(147, 351);
	groun8->GetTransform()->SetScale(200, 6);
	const auto groundCCollision8 = std::make_shared<CCollisionBox>(groun8.get(), CollisionGroup::Ground);
	groun8->AddComponent(groundCCollision8);
	const auto groundCTexture8 = std::make_shared<CRender>(groun8.get(), groundTexture, true);
	groun8->AddComponent(groundCTexture8);
	scene.Add(groun8);
	//GROUND9
	const auto ground9 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground9->GetTransform()->SetPosition(287, 399);
	ground9->GetTransform()->SetScale(200, 6);
	const auto groundCCollision9 = std::make_shared<CCollisionBox>(ground9.get(), CollisionGroup::Ground);
	ground9->AddComponent(groundCCollision9);
	const auto groundCTexture9 = std::make_shared<CRender>(ground9.get(), groundTexture, true);
	ground9->AddComponent(groundCTexture9);
	scene.Add(ground9);
	//GROUND10
	const auto ground10 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground10->GetTransform()->SetPosition(146, 446);
	ground10->GetTransform()->SetScale(331, 6);
	const auto groundCCollision10 = std::make_shared<CCollisionBox>(ground10.get(), CollisionGroup::Ground);
	ground10->AddComponent(groundCCollision10);
	const auto groundCTexture10 = std::make_shared<CRender>(ground10.get(), groundTexture, true);
	ground10->AddComponent(groundCTexture10);
	scene.Add(ground10);
	//GROUND11
	const auto ground11 = std::make_shared<GameObject>(std::string{ "Ladder" });
	ground11->GetTransform()->SetPosition(287, 541);
	ground11->GetTransform()->SetScale(45, 6);
	const auto groundCCollision11 = std::make_shared<CCollisionBox>(ground11.get(), CollisionGroup::Ground);
	ground11->AddComponent(groundCCollision11);
	const auto groundCTexture11 = std::make_shared<CRender>(ground11.get(), groundTexture, true);
	ground11->AddComponent(groundCTexture11);
	scene.Add(ground11);
#pragma endregion Ground

#pragma region BurgerIngredients

	//COMMON RESOURCES
	const auto pattyTexture = ResourceManager::GetInstance().LoadTexture("BurgerIngredients.png");
	//TRYOUT PATTY
	const auto pat = std::make_shared<GameObject>(std::string{ "supreme patty" });
	pat->GetTransform()->SetPosition(50, 50);
	const auto pattyIngredientComp = std::make_shared<CBurgerIngredient>(pat.get(), Ingredient::BunTop);
	pat->AddComponent(pattyIngredientComp);
	auto vector = pattyIngredientComp->ConstructChildren(pattyTexture);
	for(auto e : vector)
	{
		e->SetParent(pat);
		scene.Add(e);
	}
	scene.Add(pat);

	//SECOND PATTY
	const auto pat2 = std::make_shared<GameObject>(std::string{ "second supree patty" });
	pat2->GetTransform()->SetPosition(50, 130);
	const auto pattyIngredientComp2 = std::make_shared<CBurgerIngredient>(pat2.get(), Ingredient::BunTop);
	pat2->AddComponent(pattyIngredientComp2);
	auto vector2 = pattyIngredientComp2->ConstructChildren(pattyTexture);
	for (auto e : vector2)
	{
		e->SetParent(pat2);
		scene.Add(e);
	}
	scene.Add(pat2);

#pragma endregion BurgerIngredients

//#pragma region Plates

	const auto plate = std::make_shared<GameObject>(std::string{ "plate" });
	plate->GetTransform()->SetPosition(35, 439);
	plate->GetTransform()->SetScale(160, 5);
	const auto plateTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto plateCRender = std::make_shared<CRender>(plate.get(), plateTexture);
	plate->AddComponent(plateCRender);
	const auto plateCCollision = std::make_shared<CCollisionBox>(plate.get(), CollisionGroup::Plate);
	plate->AddComponent(plateCCollision);
	const auto plateCPlate = std::make_shared<CPlate>(plate.get(), true);
	plate->AddComponent(plateCPlate);

	scene.Add(plate);

	//1//
	const auto plate1 = std::make_shared<GameObject>(std::string{ "plate" });
	plate1->GetTransform()->SetPosition(35, 162);
	plate1->GetTransform()->SetScale(160, 5);
	const auto plateCRender1 = std::make_shared<CRender>(plate1.get(), plateTexture);
	plate1->AddComponent(plateCRender1);
	const auto plateCCollision1 = std::make_shared<CCollisionBox>(plate1.get(), CollisionGroup::Plate);
	plate1->AddComponent(plateCCollision1);
	const auto plateCPlate1 = std::make_shared<CPlate>(plate1.get());
	plate1->AddComponent(plateCPlate1);

	scene.Add(plate1);
	//2//
	const auto plate2 = std::make_shared<GameObject>(std::string{ "plate" });
	plate2->GetTransform()->SetPosition(35, 100);
	plate2->GetTransform()->SetScale(160, 5);
	const auto plateCRender2 = std::make_shared<CRender>(plate2.get(), plateTexture);
	plate2->AddComponent(plateCRender2);
	const auto plateCCollision2 = std::make_shared<CCollisionBox>(plate2.get(), CollisionGroup::Plate);
	plate2->AddComponent(plateCCollision2);
	const auto plateCPlate2 = std::make_shared<CPlate>(plate2.get());
	plate2->AddComponent(plateCPlate2);

	scene.Add(plate2);

//#pragma endregion Plates
	
	//PAWN
	const auto peterPepper = std::make_shared<GameObject>(std::string{ "Peter" });
	peterPepper->GetTransform()->SetPosition(200, 200);
	peterPepper->GetTransform()->SetScale(44, 44);
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