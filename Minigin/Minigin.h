#pragma once
struct SDL_Window;
class SceneObject;

class Minigin
{
public:
	void Initialize();
	void InitializeObjects(std::vector < std::shared_ptr<SceneObject>>& objects) const;
	void LoadGame() const;
	void Cleanup();
	void Run();
private:
	static const int MsPerFrame = 16; //16 for 60 fps, 33 for 30 fps
	SDL_Window* m_Window{};
};