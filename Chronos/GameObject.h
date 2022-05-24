#pragma once
#include "CBase.h"

class CTransform;

class GameObject final
{
public:
	explicit GameObject(std::string name);
	~GameObject() = default;
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
	std::shared_ptr<GameObject> GetParent();
	void SetParent(std::shared_ptr<GameObject> parent);

	std::vector<std::shared_ptr<GameObject>>& GetChildren() { return m_pChildren; }
private:
	void AddChild(std::shared_ptr<GameObject> child);
	void RemoveChild(std::shared_ptr<GameObject> child);

	std::shared_ptr<GameObject> m_pParent;
	std::vector<std::shared_ptr<GameObject>> m_pChildren;
	CTransform* m_pCTransform = nullptr;
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