#pragma once
class GameObject;

class CBase
{
public:
	CBase(GameObject* gameObject) : m_OwnerObject{ gameObject } {};
	CBase() = default;
	virtual ~CBase() {};

	CBase(const CBase& other) = delete;
	CBase(CBase&& other) = delete;
	CBase& operator=(const CBase& other) = delete;
	CBase& operator=(CBase&& other) = delete;

	GameObject* GetOwner() const { return m_OwnerObject; };

	virtual void Update(float) {};
	virtual void Render() const {};

protected:
	GameObject* m_OwnerObject;
};