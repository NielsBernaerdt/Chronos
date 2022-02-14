#pragma once
#include "Transform.h"
#include "SceneObject.h"
#include <vector>

class CBase;

class GameObject final : public SceneObject
{
public:
	GameObject() = default;
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

	void Update(float deltaTime) override;
	void Render() const;
	void SetPosition(float x, float y);
	void AddComponent(CBase* component);

private:
	Transform m_Transform;
	std::vector<CBase*> m_pComponents;
};