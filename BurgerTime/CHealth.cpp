#include "CHealth.h"
#include "GameState.h"
#include "CPeterPepper.h"
#include "CMrHotDog.h"

void CHealth::SetHealth(int hp)
{
	m_Health = hp;
	if (m_Health <= 0)
	{
		m_OwnerObject->Notify(m_OwnerObject, Event::ActorDied);
	}
}

void CHealth::Damage()
{
	--m_Health;

	auto peterComp = dynamic_cast<CPeterPepper*>(m_OwnerObject->GetComponent<CPeterPepper>());
	if(peterComp != nullptr)
	{
		m_OwnerObject->GetTransform()->SetPosition(590, 35);

		if (m_Health == 0)
		{
			m_OwnerObject->Notify(m_OwnerObject, Event::ActorDied);
		}
		else
		{
			m_OwnerObject->Notify(m_OwnerObject, Event::ActorDamaged);
		}
	}
	else
	{
		auto hotdogComp = dynamic_cast<CMrHotDog*>(m_OwnerObject->GetComponent<CMrHotDog>());
		if (hotdogComp != nullptr)
		{
			m_OwnerObject->GetTransform()->SetPosition(-200, -200);

			if (m_Health == 0)
			{
				m_OwnerObject->Notify(m_OwnerObject, Event::NPCKilled);
			}
		}
	}
}