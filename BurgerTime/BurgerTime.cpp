#include "BurgerTime.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#include <SDL.h>
#pragma warning (pop)

#include "InputManager.h"
#include "Commands.h"
#include "CommandsBase.h"
#include "SceneManager.h"
#include "Renderer.h"
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

void BurgerTime::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");

	//TutorialScene(scene);
	//SceneGraphTestScene(scene);
	ObserverScene(scene);

	InitializeObjects(scene.GetObjects());
}

//OWN SCENES//
void BurgerTime::TutorialScene(Scene& scene) const
{
	auto parentObject = std::make_shared<GameObject>(std::string{ "TutorialParent" });
	parentObject->GetTransform()->SetPosition(300, 200);

	//Background image
	const auto background = std::make_shared<GameObject>(std::string{ "Background" });
	background->GetTransform()->SetPosition(0, 0);
	auto bgTexture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	const auto bgCRender = std::make_shared<CRender>(background.get(), bgTexture);
	background->AddComponent(bgCRender);
	scene.Add(background);

	background->SetParent(parentObject);

	//Make FPS object
	const auto fpsCounter = std::make_shared<GameObject>(std::string{ "FPSCounter" });
	fpsCounter->GetTransform()->SetPosition(100, 100);
	const auto fpsCText = std::make_shared<CText>(fpsCounter.get(), "FPS Counter", 36);
	fpsCounter->AddComponent(fpsCText);
	const auto fpsComp = std::make_shared<CFPS>(fpsCounter.get());
	fpsCounter->AddComponent(fpsComp);
	auto fpsTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto fpsCRender = std::make_shared<CRender>(fpsCounter.get(), fpsTexture);
	fpsCounter->AddComponent(fpsCRender);
	scene.Add(fpsCounter);

	fpsCounter->SetParent(parentObject);

	//Make logo object
	const auto logo = std::make_shared<GameObject>(std::string{ "Logo" });
	logo->GetTransform()->SetPosition(216, 180);
	auto logoTexture = ResourceManager::GetInstance().LoadTexture("logo.png");
	const auto logoCRender = std::make_shared<CRender>(logo.get(), logoTexture);
	logo->AddComponent(logoCRender);
	scene.Add(logo);

	logo->SetParent(parentObject);

	//Make title object
	const auto title = std::make_shared<GameObject>(std::string{ "Title" });
	title->GetTransform()->SetPosition(80, 20);
	const auto titleCText = std::make_shared<CText>(title.get(), "Programming 4 Assignment", 36);
	title->AddComponent(titleCText);
	auto titleTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto titleCRender = std::make_shared<CRender>(title.get(), titleTexture);
	title->AddComponent(titleCRender);
	scene.Add(title);

	title->SetParent(parentObject);

	scene.Add(parentObject);

	//PAWN
	const auto peterPepper = std::make_shared<GameObject>(std::string{ "Peter" });
	peterPepper->GetTransform()->SetPosition(200, 200);
	const auto peterTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto peterCRender = std::make_shared<CRender>(peterPepper.get(), peterTexture);
	peterPepper->AddComponent(peterCRender);
	scene.Add(peterPepper);
	m_Input->SetPawn(peterPepper.get());
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

	//todo fix changing parent runtime
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

void BurgerTime::ConfigureInput()
{
	m_Input->BindCommandToButton(ControllerButton::ButtonA, std::make_unique<Fart>(nullptr));
	m_Input->BindCommandToButton(ControllerButton::ButtonX, std::make_unique<Duck>(nullptr));
}