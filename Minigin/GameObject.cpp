#include "ChronosPCH.h"
#include "GameObject.h"

void GameObject::Initialize()
{
	for (const auto& obj : m_Children)
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
	for (const auto& obj : m_Children)
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
	for (const auto& obj : m_Children)
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
//SCENEGRAPH//
std::shared_ptr<GameObject> GameObject::GetParent()
{
	return m_Parent;
}
void GameObject::SetParent(std::shared_ptr<GameObject> parent)
{
	if(parent == nullptr)
	{
		//todo stuff
		std::cout << "Help\n";
	}

	if (m_Parent)
		m_Parent->RemoveChild(std::shared_ptr<GameObject>(this));
	m_Parent = parent;
	m_Parent->AddChild(std::shared_ptr<GameObject>(this));

	//todo: opdate position/rotation/scale
}
void GameObject::AddChild(std::shared_ptr<GameObject> child)
{
	//if(child->GetParent())
	//	child->GetParent()->RemoveChild(child);
	//child->SetParent(std::shared_ptr<GameObject>(this));
	m_Children.push_back(child);
	//todo: opdate position/rotation/scale
}
void GameObject::RemoveChild(std::shared_ptr<GameObject> child)
{
	auto noDiscardTest = 
	std::remove_if(m_Children.begin(), m_Children.end(), [&](std::shared_ptr<GameObject> c)
		{
			return c.get() == child.get();
		});

	// child->SetParent(nullptr); //this is not needed?? it gets set to new parent immediatly afterwards
	//todo: opdate position/rotation/scale
}