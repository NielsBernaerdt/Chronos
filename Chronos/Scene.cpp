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