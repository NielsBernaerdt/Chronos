#pragma once
#include <iostream>
#include <vector>

#include "CBase.h"

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
	void AddComponent(std::shared_ptr<CBase> component);
	template <typename T>
	std::shared_ptr<CBase> GetComponent() const;
	CTransform* GetTransform();

	std::string GetName() { return m_Name; }

private:
	std::vector<std::shared_ptr<CBase>> m_pComponents;
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
std::shared_ptr<CBase> GameObject::GetComponent() const
{
	for (auto e : m_pComponents) 
	{
		if (std::dynamic_pointer_cast<T>(e))
			return e;
	}
	std::shared_ptr<CBase> emptyComponent = nullptr;
	return emptyComponent;
}