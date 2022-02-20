#include "MiniginPCH.h"
#include "Minigin.h"
#include <chrono>
#include <thread>
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "CText.h"
#include "CRender.h"
#include "CFPS.h"
#include "CTransform.h"
#include "GameObject.h"
#include "Texture2D.h"
#include "Scene.h"

using namespace std;

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

void Minigin::Initialize()
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
		640,
		480,
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
void Minigin::LoadGame() const
{
	auto& scene = SceneManager::GetInstance().CreateScene("Demo");

	//Test Scenegraph thingy
	//auto parentObject = std::make_shared<GameObject>();

	//Background image
	auto background = std::make_shared<GameObject>();
	auto bgCTransform = std::make_shared<CTransform>(background.get(), 0, 0);
	background->AddComponent(bgCTransform);
	auto bgTexture = ResourceManager::GetInstance().LoadTexture("background.jpg");
	auto bgCRender = std::make_shared<CRender>(background.get(), bgTexture);
	background->AddComponent(bgCRender);
	scene.Add(background);
	//parentObject->AddChild(background.get());

	//Make FPS object
	auto fpsCounter = std::make_shared<GameObject>();
	auto fpsCTransform = std::make_shared<CTransform>(fpsCounter.get(), 10, 10);
	fpsCounter->AddComponent(fpsCTransform);
	auto fpsCText = std::make_shared<CText>( fpsCounter.get(), "FPS Counter", 36 );
	fpsCounter->AddComponent(fpsCText);
	auto fpsComp = std::make_shared<CFPS>(fpsCounter.get());
	fpsCounter->AddComponent(fpsComp);
	auto fpsTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	auto fpsCRender = std::make_shared<CRender>(fpsCounter.get(), fpsTexture);
	fpsCounter->AddComponent(fpsCRender);
	scene.Add(fpsCounter);
	//parentObject->AddChild(fpsCounter.get());

	//Make logo object
	auto logo = std::make_shared<GameObject>();
	auto logoCTransform = std::make_shared<CTransform>(logo.get(), 216, 180);
	logo->AddComponent(logoCTransform);
	auto logoTexture = ResourceManager::GetInstance().LoadTexture("logo.png");
	auto logoCRender = std::make_shared<CRender>(logo.get(), logoTexture);
	logo->AddComponent(logoCRender);
	scene.Add(logo);
	//parentObject->AddChild(logo.get());

	//Make title object
	auto title = std::make_shared<GameObject>();
	auto titleCTransform = std::make_shared<CTransform>(title.get(), 80, 20);
	title->AddComponent(titleCTransform);
	auto titleCText = std::make_shared<CText>(title.get(), "Programming 4 Assignment", 36);
	title->AddComponent(titleCText);
	auto titleTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	auto titleCRender = std::make_shared<CRender>(title.get(), titleTexture);
	title->AddComponent(titleCRender);
	scene.Add(title);
	//parentObject->AddChild(title.get());

	//scene.Add(parentObject);

	InitializeObjects(scene.GetObjects());
}

void Minigin::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
}

void Minigin::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	LoadGame();

	{
		auto& renderer = Renderer::GetInstance();
		auto& sceneManager = SceneManager::GetInstance();
		auto& input = InputManager::GetInstance();

		bool doContinue = true;
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;

			doContinue = input.ProcessInput();
			sceneManager.Update(deltaTime);
			renderer.Render();

			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(m_MsPerFrame) - std::chrono::high_resolution_clock::now());
			this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();
}

void Minigin::InitializeObjects(std::vector < std::shared_ptr<SceneObject>>& objects) const
{
	for (auto e : objects)
	{
		e->Initialize();
	}
}