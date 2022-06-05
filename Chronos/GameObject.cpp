#include "ChronosPCH.h"
#include "GameObject.h"

#include "CRender.h"
#include "CTransform.h"
#include "BObserver.h"

#pragma region Components
GameObject::GameObject(std::string name)
	:m_Name(name)
{
	AddComponent(std::make_unique<CTransform>(this));
}
GameObject::~GameObject()
{
	//todo memory for boservers clean??
	//for(size_t i{}; i < m_pObservers.size(); ++i)
	//{
	//	delete m_pObservers[i];
	//	m_pObservers[i] = nullptr;
	//}
}


void GameObject::Initialize()
{
	for (const auto& obj : m_pChildren)
	{
		obj->Initialize();
	}
	for (const auto& comp : m_pComponents)
	{
		comp->Initialize();
	}
}

void GameObject::Update(float deltaTime)
{
	for (const auto& obj : m_pChildren)
	{
		obj->Update(deltaTime);
	}
	for (const auto& comp : m_pComponents)
	{
		comp->Update(deltaTime);
	}
}

void GameObject::Render() const
{
	for (const auto& obj : m_pChildren)
	{
		obj->Render();
	}
	//todo dont dynamiccast on hot code path
	CBase* renderComp = GetComponent<CRender>();
	if (renderComp)
		dynamic_cast<CRender*>(renderComp)->Render();
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
GameObject* GameObject::GetParent()
{
	return m_pParent;
}
void GameObject::SetParent(GameObject* parent)
{
	//if (m_pParent)
	//	m_pParent->RemoveChild(std::shared_ptr<GameObject>(this));
	m_pParent = parent;
	m_pParent->AddChild(this);
}
void GameObject::AddChild(GameObject* child)
{
	m_pChildren.push_back(child);
}
void GameObject::RemoveChild(GameObject* child)
{
	const auto it = std::ranges::find(m_pChildren, child);

	if (it == m_pChildren.end())
	{
		std::cout << "GameObject::RemoveChild - GameObject to remove is not attached to this GameObject!" << std::endl;
		return;
	}

	m_pChildren.erase(it);


	// child->SetParent(nullptr); //this is not needed?? it gets set to new parent immediatly afterwards
	//todo: opdate position/rotation/scale
}
#pragma endregion Scenegraph

#pragma region Observers
void GameObject::AddObserver(std::shared_ptr<BObserver> observer)
{
	m_pObservers.push_back(observer);
}
void GameObject::RemoveObserver(std::shared_ptr<BObserver> observer)
{
	const auto it = std::ranges::find(m_pObservers, observer);

	if (it == m_pObservers.end())
	{
		std::cout << "GameObject::RemoveObserver - Observer to remove is not attached to this GameObject!" << std::endl;
		return;
	}

	m_pObservers.erase(it);
}
void GameObject::Notify(GameObject* gameObject, Event event)
{
	for(auto observer : m_pObservers)
	{
		observer->Notify(gameObject, event);
	}
}
#pragma endregion Observers