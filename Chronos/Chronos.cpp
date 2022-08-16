#include "ChronosPCH.h"
#include "Chronos.h"
#include <chrono>
#include "AudioManager.h"
#include "Game.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "Renderer.h"
#include "ResourceManager.h"
#include "GameObject.h"
#include "Scene.h"
#include "SoundEffect.h"

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
		630,
		630,
		SDL_WINDOW_OPENGL
	);
	if (m_Window == nullptr) 
	{
		throw std::runtime_error(std::string("SDL_CreateWindow Error: ") + SDL_GetError());
	}

	Renderer::GetInstance().Init(m_Window);
	AudioManager::GetInstance().Init();
}

/**
 * Code constructing the scene world starts here
 */

 bool Chronos::LoadGame() const
{
	 bool invalidFile = m_pGame->SetupGameScenes();
	 if (invalidFile)
	 {
		 std::cout << "Wrong file layout. Press a key to exit...\n";
		 std::cin.get();
		 return true;
	 }

	 InitializeObjects();
	 return false;
}

void Chronos::Cleanup()
{
	Renderer::GetInstance().Destroy();
	SDL_DestroyWindow(m_Window);
	m_Window = nullptr;
	SDL_Quit();
	delete m_pGame;
	m_pGame = nullptr;
}

void Chronos::Run()
{
	Initialize();

	// tell the resource manager where he can find the game data
	ResourceManager::GetInstance().Init("../Data/");

	const auto& renderer = Renderer::GetInstance();
	auto& sceneManager = SceneManager::GetInstance();
	
	bool doContinue = true;
	
	if (LoadGame()) doContinue = false;
	auto inputManager = ConfigureInput();

	{
		auto lastTime = std::chrono::high_resolution_clock::now();
		while (doContinue)
		{
			auto currentTime = std::chrono::high_resolution_clock::now();
			const float deltaTime = std::chrono::duration<float>(currentTime - lastTime).count();
			lastTime = currentTime;


			if (inputManager->ProcessInput() == false)
					doContinue = false;
			int mouseX, mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			InputManager::SetMousePos(mouseX, mouseY);

			sceneManager.Update(deltaTime);
			renderer.Render();
			sceneManager.EraseObjects();
			sceneManager.AddSpawnedObjects();
			auto sleepTime = std::chrono::duration_cast<std::chrono::duration<float>>(currentTime + std::chrono::milliseconds(m_MsPerFrame) - std::chrono::high_resolution_clock::now());
			std::this_thread::sleep_for(sleepTime);
		}
	}

	Cleanup();

	delete inputManager;
	inputManager = nullptr;

	AudioManager::GetInstance().LeaveThread(true);
}

void Chronos::InitializeObjects() const
{
	SceneManager::GetInstance().InitializeObjects();
}