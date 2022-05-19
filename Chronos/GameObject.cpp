#include "ChronosPCH.h"
#include "GameObject.h"

#include "CRender.h"
#include "CTransform.h"


GameObject::GameObject(std::string name)
	:m_Name(name)
{
	std::shared_ptr<CTransform> pCTransform = std::make_shared<CTransform>(this);
	AddComponent(pCTransform);
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
	for (const auto& comp : m_pComponents)
	{
		comp->Render();
	}
}

void GameObject::AddComponent(std::shared_ptr<CBase> component)
{
	m_pComponents.push_back(component);
}

CTransform* GameObject::GetTransform()
{
	if (m_pCTransform == nullptr)
	{
		m_pCTransform = dynamic_cast<CTransform*>(GetComponent<CTransform>().get());
	}
	return m_pCTransform;
}

//SCENEGRAPH//
std::shared_ptr<GameObject> GameObject::GetParent()
{
	return m_pParent;
}
void GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	if (m_pParent)
		m_pParent->RemoveChild(std::shared_ptr<GameObject>(this));
	m_pParent = parent;
	m_pParent->AddChild(std::shared_ptr<GameObject>(this));

	//todo: opdate position/rotation/scale
}
void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	m_pChildren.push_back(child);
	//todo: opdate position/rotation/scale
}
void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
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