#pragma once
#include "Singleton.h"

class Scene;
class SceneManager final : public Singleton<SceneManager>
{
public:
	Scene& CreateScene(const std::string& name);

	void InitializeObjects();
	void Update(float deltaTime);
	void Render();

	std::vector<std::shared_ptr<Scene>>& GetScenes() { return m_Scenes; }
	Scene* GetScene(int index) { return m_Scenes[index].get(); }
	int GetActiveScene();
	bool IsGameActive() const { return m_IsGameActive; }
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes;
	bool m_IsGameActive{ false };
};