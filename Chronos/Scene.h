#pragma once
#include "SceneManager.h"

class GameObject;
class Scene
{
	friend Scene& SceneManager::CreateScene(const std::string& name);
public:
	void Add(const std::shared_ptr<GameObject>& object);
	std::vector < std::shared_ptr<GameObject>>& GetObjects() { return m_Objects; }

	void Update(float deltaTime);
	void Render() const;

	void SetActive(bool active);
	bool IsActive() const { return m_IsActive; }

	~Scene();
	Scene(const Scene& other) = delete;
	Scene(Scene&& other) = delete;
	Scene& operator=(const Scene& other) = delete;
	Scene& operator=(Scene&& other) = delete;

private:
	explicit Scene(const std::string& name);

	std::string m_Name;
	bool m_IsActive{ false };
	std::vector < std::shared_ptr<GameObject>> m_Objects{};

	static unsigned int m_IdCounter;
};