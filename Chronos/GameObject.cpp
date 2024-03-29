#include "ChronosPCH.h"
#include "GameObject.h"
#include "CRender.h"
#include "CTransform.h"

#pragma region Components
GameObject::GameObject(std::string name)
	:m_Name(name)
{
	AddComponent(std::make_unique<CTransform>(this));
}
GameObject::~GameObject()
{
	m_pChildren.clear();
}

void GameObject::Initialize()
{
	for (const auto& comp : m_pComponents)
	{
		comp->Initialize();
	}

	CBase* pComp = GetComponent<CRender>();
	if (pComp)
		m_pRender = dynamic_cast<CRender*>(pComp);
}

void GameObject::Update(float deltaTime)
{
	for (const auto& comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::Render() const
{
	if(m_pRender) m_pRender->Render();
}

void GameObject::AddComponent(std::unique_ptr<CBase> component)
{
	m_pComponents.push_back(std::move(component));
}

CTransform* GameObject::GetTransform()
{
	if (m_pCTransform == nullptr)
	{
		m_pCTransform = dynamic_cast<CTransform*>(GetComponent<CTransform>());
	}
	return m_pCTransform;
}
#pragma endregion Components

#pragma region Scenegraph
GameObject* GameObject::GetParent() const
{
	return m_pParent;
}
void GameObject::SetParent(GameObject* parent, std::shared_ptr<GameObject> child)
{
	m_pParent = parent;
	m_pParent->AddChild(child);
}
void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_pChildren.push_back(child);
}
#pragma endregion Scenegraph