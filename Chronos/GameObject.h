#pragma once
#include <vector>
#include <string>
#include <memory>
#include "CBase.h"
#include "CTransform.h"

class CRender;
enum class Event;
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

	const std::string& GetName() const { return m_Name; }

private:
	std::vector<std::unique_ptr<CBase>> m_pComponents;
	std::string m_Name{};

	//scenegraph
public:
	GameObject* GetParent() const;
	void SetParent(GameObject* parent, std::shared_ptr<GameObject> child);

	std::vector<std::shared_ptr<GameObject>> GetChildren() const { return m_pChildren; }
private:
	void AddChild(std::shared_ptr<GameObject> child);

	GameObject* m_pParent = nullptr;
	std::vector<std::shared_ptr<GameObject>> m_pChildren;
	CTransform* m_pCTransform = nullptr;
	CRender* m_pRender = nullptr;
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