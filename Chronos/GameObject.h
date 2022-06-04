#pragma once
#include <iostream>
#include <vector>

#include "CBase.h"
#include "CTransform.h"

enum class Event;
class BObserver;
class CTransform;

class GameObject final
{
public:
	explicit GameObject(std::string name);
	~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Initialize();
	void Update(float deltaTime);
	void Render() const;
	void AddComponent(std::unique_ptr<CBase> component);
	template <typename T>
	CBase* GetComponent() const;
	CTransform* GetTransform();

	std::string GetName() { return m_Name; }

private:
	std::vector<std::unique_ptr<CBase>> m_pComponents;
	std::string m_Name;

	//scenegraph
public:
	GameObject* GetParent();
	void SetParent(GameObject* parent);

	std::vector<GameObject*> GetChildren() { return m_pChildren; }
private:
	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);

	GameObject* m_pParent = nullptr;
	std::vector<GameObject*> m_pChildren;
	CTransform* m_pCTransform = nullptr;

	//Observers
public:
	void AddObserver(BObserver* observer);
	void RemoveObserver(BObserver* observer);

	void Notify(GameObject* gameObject, Event event);

private:
	std::vector<BObserver*> m_pObservers;
};

template <typename T>
CBase* GameObject::GetComponent() const
{
	for (const auto& e : m_pComponents)
	{
		if (dynamic_cast<T*>(e.get()))
			return e.get();
	}

	return nullptr;
}

