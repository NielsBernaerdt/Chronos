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
	void EraseObjects();

	std::vector<std::shared_ptr<Scene>>& GetScenes() { return m_Scenes; }
	Scene* GetScene(int index) { return m_Scenes[index].get(); }
	int GetActiveSceneIdx();
	Scene* GetActiveScene();
	bool IsGameActive() const { return m_IsGameActive; }
	void SetGameNonActive() { m_IsGameActive = false; }
	void OpenScene(int idx);
private:
	friend class Singleton<SceneManager>;
	SceneManager() = default;
	std::vector<std::shared_ptr<Scene>> m_Scenes;
	bool m_IsGameActive{ false };
};