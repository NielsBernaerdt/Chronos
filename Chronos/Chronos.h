#pragma once
#include <vector>
#include <memory>

#include "Game.h"

class GameObject;
struct SDL_Window;

class Chronos
{
public:
	Chronos(Game* pGame) : m_pGame(pGame) {};

	void Initialize();
	void InitializeObjects(const std::vector<std::shared_ptr<GameObject>>& objects) const;
	bool LoadGame() const;
	void Cleanup();
	void Run();

private:
	static constexpr int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_Window{};
	Game* m_pGame = nullptr;

	virtual std::vector<InputManager*> ConfigureInput() const {
		return m_pGame->ConfigureInput();
	}

	bool m_RestartGame{ false };
};