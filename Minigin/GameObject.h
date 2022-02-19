#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <vector>
#include "CBase.h"
#include "CText.h"

class GameObject final : public SceneObject
{
public:
	GameObject() = default;
	virtual ~GameObject() = default;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Initialize() override;
	void Update(float deltaTime) override;
	void Render() const;
	void SetPosition(float x, float y);
	void AddComponent(std::shared_ptr<CBase> component);
	template <typename T>
	std::shared_ptr<CBase> GetComponent() const;

private:
	Transform m_Transform;
	std::vector<std::shared_ptr<CBase>> m_pComponents;
};

template <typename T>
std::shared_ptr<CBase> GameObject::GetComponent() const
{
	//std::cout << typeid(T).name() << "\n";
	//std::cout << typeid(std::make_shared<T>(this)).name() << "\n";

	for (auto e : m_pComponents) 
	{
		if (std::dynamic_pointer_cast<T>(e))
			return e;
	}
	std::shared_ptr<CBase> emptyComponent = nullptr;
	return emptyComponent;
}