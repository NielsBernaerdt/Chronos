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
	void LoadGame() const;
	void Cleanup();
	void Run();

private:
	static constexpr int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_Window{};
	Game* m_pGame = nullptr;

	virtual void ConfigureInput() const {
		m_pGame->ConfigureInput(m_Input);
	}

protected:
	InputManager* m_Input = nullptr;
};