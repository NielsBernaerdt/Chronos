#include "CHealth.h"
#include "../BurgerTime/GameState.h"

void CHealth::SetHealth(int hp)
{
	m_Health = hp;
	if (m_Health <= 0)
	{
		m_OwnerObject->Notify(m_OwnerObject, Event::ActorDied);
	}
}