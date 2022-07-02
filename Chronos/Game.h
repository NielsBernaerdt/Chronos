#pragma once
#include <vector>

class Scene;
class InputManager;

class Game
{
public:
	Game() = default;
	virtual ~Game() = default;

	Game(const Game& other) = delete;
	Game(Game&& other) noexcept = delete;
	Game& operator=(const Game& other) = delete;
	Game& operator=(Game&& other) noexcept = delete;

	virtual bool SetupLevelLayout(Scene& scene) = 0;
	virtual InputManager* ConfigureInput() = 0;
};
