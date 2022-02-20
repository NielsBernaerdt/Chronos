#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include <algorithm>

void GameObject::Initialize()
{
	for(const auto& child : m_pChilds)
	{
		child->Initialize();
	}
	for (const auto& comp : m_pComponents)
	{
		comp->Initialize();
	}
}

void GameObject::Update(float deltaTime)
{
	for (const auto& child : m_pChilds)
	{
		child->Update(deltaTime);
	}
	for (const auto& comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::Render() const
{
	for (const auto& child : m_pChilds)
	{
		child->Render();
	}
	for (const auto& comp : m_pComponents)
	{
		comp->Render();
	}
}

void GameObject::AddChild(GameObject* childObject)
{
	m_pChilds.push_back(childObject);
}

void GameObject::AddComponent(std::shared_ptr<CBase> component)
{
	m_pComponents.push_back(component);
}
