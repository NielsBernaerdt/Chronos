#pragma once
#include "CBase.h"
#include "GameObject.h"
#include "../BurgerTime/Achievements.h"

class CHealth : public CBase
{
public:
	CHealth(GameObject* gameObject) : CBase(gameObject) {};
	~CHealth() override = default;
	CHealth(const CHealth& other) = delete;
	CHealth(CHealth&& other) noexcept = delete;
	CHealth& operator=(const CHealth& other) = delete;
	CHealth& operator=(CHealth&& other) noexcept = delete;

	void SetHealth(int hp)
	{
		m_Health = hp;
		if(m_Health <= 0)
		{
			m_OwnerObject->Notify(m_OwnerObject, Event::ActorDied);
		}
	}
	int GetHealth() const { return m_Health; }

private:
	int m_Health{};
};
