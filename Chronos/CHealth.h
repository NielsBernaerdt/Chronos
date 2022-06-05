#pragma once
#include "CBase.h"
#include "GameObject.h"

class CHealth : public CBase
{
public:
	CHealth(GameObject* gameObject, int health = 3) : CBase(gameObject), m_Health(health) {}
	~CHealth() override = default;
	CHealth(const CHealth& other) = delete;
	CHealth(CHealth&& other) noexcept = delete;
	CHealth& operator=(const CHealth& other) = delete;
	CHealth& operator=(CHealth&& other) noexcept = delete;

	void SetHealth(int hp);
	int GetHealth() const { return m_Health; }
	void Damage();
private:
	int m_Health{};
};
