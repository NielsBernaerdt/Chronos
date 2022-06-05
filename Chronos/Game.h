#pragma once

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

	virtual void SetupObjects(Scene& scene) = 0;
	virtual void ConfigureInput(InputManager* input) const = 0;
};
