#pragma once
class GameObject;

class CBase
{
public:
	explicit CBase(GameObject* gameObject) : m_OwnerObject{ gameObject } {};
	virtual ~CBase() = default;;

	CBase(const CBase& other) = delete;
	CBase(CBase&& other) = delete;
	CBase& operator=(const CBase& other) = delete;
	CBase& operator=(CBase&& other) = delete;

	virtual void Initialize() {};
	virtual void Update(float) {};
	virtual void Render() const {};

protected:
	GameObject* m_OwnerObject;
};