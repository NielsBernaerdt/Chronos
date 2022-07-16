#include "ChronosPCH.h"
#include "Scene.h"
#include "GameObject.h"

unsigned int Scene::m_IdCounter = 0;

Scene::Scene(const std::string& name) : m_Name(name) {}

Scene::~Scene() = default;

void Scene::Add(const std::shared_ptr<GameObject>& object)
{
	m_Objects.push_back(object);

	if(SceneManager::GetInstance().IsGameActive() == true)
		object->Initialize();
}

void Scene::Update(float deltaTime)
{
	for(auto& object : m_Objects)
	{
		object->Update(deltaTime);
	}
}

void Scene::Render() const
{
	for (const auto& object : m_Objects)
	{
		object->Render();
	}
}

void Scene::SetActive(bool active)
{
	if (active == true)
	{
		for (auto scene : SceneManager::GetInstance().GetScenes())
		{
			if (scene != nullptr)
				scene->SetActive(false);
		}
	}
	m_IsActive = active;
}

void Scene::RemoveObject(GameObject* gameObject)
{
	m_ObjectsToDelete.push_back(gameObject);
}

void Scene::EraseObjects()
{
	for(auto obj : m_ObjectsToDelete)
	{
		std::vector<std::shared_ptr<GameObject>>::iterator i =	std::find_if(m_Objects.begin(), m_Objects.end(),
				[&](std::shared_ptr<GameObject> e) { return e.get() == obj; });

		m_Objects.erase(i);
	}
	m_ObjectsToDelete = std::vector <GameObject*>{};
}