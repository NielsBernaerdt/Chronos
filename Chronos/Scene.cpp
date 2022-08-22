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
		if(object)
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
	//for (auto child : gameObject->GetChildren())
	//{
	//	m_ObjectsToDelete.push_back(child.get());
	//}
}

void Scene::ClearScene()
{
	for(const auto& object : m_Objects)
	{
		m_ObjectsToDelete.push_back(object.get());
	}
	EraseObjects();
}

void Scene::EraseObjects()
{
	if (m_ObjectsToDelete.empty())
		return;

	for(auto obj : m_ObjectsToDelete)
	{
		std::vector<std::shared_ptr<GameObject>>::iterator i =	std::find_if(m_Objects.begin(), m_Objects.end(),
				[&](std::shared_ptr<GameObject> e) { return e.get() == obj; });

		if(i != m_Objects.end())
			m_Objects.erase(i);
	}
	m_ObjectsToDelete = std::vector <GameObject*>{};
}

void Scene::SpawnObject(std::shared_ptr<GameObject> gameObject)
{
	m_ObjectsToSpawn.push_back(gameObject);
}

void Scene::AddSpawnedObjects()
{
	for (auto obj : m_ObjectsToSpawn)
	{
		Add(obj);
	}
	m_ObjectsToSpawn.clear();
}