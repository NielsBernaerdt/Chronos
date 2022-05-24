#pragma once
#include <vector>
#include <memory>

struct SDL_Window;
class GameObject;
class Scene;

class Chronos
{
public:
	void Initialize();
	static void InitializeObjects(const std::vector<std::shared_ptr<GameObject>>& objects);
	virtual void LoadGame() const = 0;
	void Cleanup();
	void Run();

private:
	static constexpr int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_Window{};
};