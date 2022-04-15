#pragma once
#include "SceneObject.h"
#include <vector>
#include "CBase.h"

class GameObject final : public SceneObject
{
public:
	GameObject() = default;
	~GameObject() override = default;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() const override;
	void AddComponent(std::shared_ptr<CBase> component);
	template <typename T>
	std::shared_ptr<CBase> GetComponent() const;

private:
	std::vector<std::shared_ptr<CBase>> m_pComponents;

	//scenegraph
public:
	std::shared_ptr<GameObject> GetParent();
	void SetParent(std::shared_ptr<GameObject> parent);
private:
	void AddChild(std::shared_ptr<GameObject> child);
	void RemoveChild(std::shared_ptr<GameObject> child);

	std::shared_ptr<GameObject> m_Parent;
	std::vector<std::shared_ptr<GameObject>> m_Children;
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