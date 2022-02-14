#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "CBase.h"

GameObject::~GameObject()
{
	for (auto e : m_pComponents)
	{
		delete e;
		e = nullptr;
	}
}

void GameObject::Update(float deltaTime)
{
	for (auto e : m_pComponents)
	{
		e->Update(deltaTime);
	}
}

void GameObject::Render() const
{
	for (auto e : m_pComponents)
	{
		e->Render();
	}
}

void GameObject::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

void GameObject::AddComponent(CBase* component)
{
	m_pComponents.push_back(component);
}