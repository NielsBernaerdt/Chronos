#pragma once
struct SDL_Window;
class SceneObject;
class Scene;

class Chronos
{
public:
	void Initialize();
	static void InitializeObjects(const std::vector < std::shared_ptr<SceneObject>>& objects);
	void LoadGame() const;
	void Cleanup();
	void Run();
private:
	static constexpr int m_MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_Window{};

	void TutorialScene(Scene& scene) const;
	void SceneGraphTestScene(Scene& scene) const;
};