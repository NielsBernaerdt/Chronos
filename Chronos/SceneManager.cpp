#include "ChronosPCH.h"
#include "SceneManager.h"

#include "GameObject.h"
#include "Scene.h"

void SceneManager::InitializeObjects()
{
	for (auto& scene : m_Scenes)
	{
		for (auto& obj : scene->GetObjects())
		{
			obj->Initialize();
		}
	}
}

void SceneManager::Update(float deltaTime)
{
	for(auto& scene : m_Scenes)
	{
		if(scene->IsActive() == true)
			scene->Update(deltaTime);
	}
}

void SceneManager::Render()
{
	for (const auto& scene : m_Scenes)
	{
		if (scene->IsActive() == true)
			scene->Render();
	}
}

Scene& SceneManager::CreateScene(const std::string& name)
{
	const auto& scene = std::shared_ptr<Scene>(new Scene(name));
	m_Scenes.push_back(scene);
	return *scene;
}

int SceneManager::GetActiveScene()
{
	int sceneIndex{ 0 };
	for(const auto& scene : m_Scenes)
	{
		if (scene->IsActive() == true)
			return sceneIndex;
		++sceneIndex;
	}
	return -1;
}