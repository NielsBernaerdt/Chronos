#include "ChronosPCH.h"
#include "Chronos.h"
#include <chrono>
#include <thread>

#include "CFPS.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "CRender.h"
#include "CText.h"
#include "CTransform.h"
#include "GameObject.h"
#include "Scene.h"


void PrintSDLVersion()
{
	SDL_version compiled{};
	SDL_version linked{};

	SDL_VERSION(&compiled);
	SDL_GetVersion(&linked);
	printf("We compiled against SDL version %d.%d.%d ...\n",
		compiled.major, compiled.minor, compiled.patch);
	printf("We are linking against SDL version %d.%d.%d.\n",
		linked.major, linked.minor, linked.patch);
}

void Chronos::Initialize()
{
	PrintSDLVersion();
	
	if (SDL_Init(SDL_INIT_VIDEO) != 0) 
	{
		throw std::runtime_error(std::string("SDL_Init Error: ") + SDL_GetError());
	}

	m_Window = SDL_CreateWindow(
		"Programming 4 assignment",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		1280,
		720,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
}

/**
 * Code constructing the scene world starts here
 */
void Chronos::LoadGame() const
{
	Scene& scene = SceneManager::GetInstance().CreateScene("Demo");

	//TutorialScene(scene);
	SceneGraphTestScene(scene);

	InitializeObjects(scene.GetObjects());
}

void Chronos::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Chronos::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		const auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto input = InputManager(0);
		input.SetUpInput();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;

			doContinue = input.ProcessInput();

			input.HandleInput();
			sceneManager.Update(deltaTime);
			renderer.Render();

			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(m_MsPerFrame) - std::chrono::high_resolution_clock::now());
			std::this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void Chronos::InitializeObjects(const std::vector < std::shared_ptr<GameObject>>& objects)
{
	for (const auto e : objects)
	{
		e->Initialize();
	}
}
//OWN SCENES//
void Chronos::TutorialScene(Scene& scene) const
{
	auto parentObject = std::make_shared<GameObject>(std::string{ "TutorialParent" });
	parentObject->GetTransform()->SetPosition(300, 200);

	//Background image
	const auto background = std::make_shared<GameObject>(std::string{"Background"});
	background->GetTransform()->SetPosition(0, 0);
	auto bgTexture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	const auto bgCRender = std::make_shared<CRender>(background.get(), bgTexture);
	background->AddComponent(bgCRender);
	scene.Add(background);

	background->SetParent(parentObject);

	//Make FPS object
	const auto fpsCounter = std::make_shared<GameObject>(std::string{"FPSCounter"});
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
	const auto logo = std::make_shared<GameObject>(std::string{"Logo"});
	logo->GetTransform()->SetPosition(216, 180);
	auto logoTexture = ResourceManager::GetInstance().LoadTexture("logo.png");
	const auto logoCRender = std::make_shared<CRender>(logo.get(), logoTexture);
	logo->AddComponent(logoCRender);
	scene.Add(logo);

	logo->SetParent(parentObject);

	//Make title object
	const auto title = std::make_shared<GameObject>(std::string{"Title"});
	title->GetTransform()->SetPosition(80, 20);
	const auto titleCText = std::make_shared<CText>(title.get(), "Programming 4 Assignment", 36);
	title->AddComponent(titleCText);
	auto titleTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	const auto titleCRender = std::make_shared<CRender>(title.get(), titleTexture);
	title->AddComponent(titleCRender);
	scene.Add(title);

	title->SetParent(parentObject);

	scene.Add(parentObject);
}
void Chronos::SceneGraphTestScene(Scene& scene) const
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