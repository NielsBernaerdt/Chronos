#include "CHealth.h"
#include <GameObject.h>
#include <SceneManager.h>
#include "Scene.h"
#include "CPoints.h"
#include "BPublisher.h"
#include "GameState.h"
#include "CTankTron.h"
#include "CTankNPC.h"

void CHealth::SetHealth(int hp)
{
	m_Health = hp;
}

void CHealth::Damage()
{
	--m_Health;

	if (!m_pPublisher)
		return;

	if (m_OwnerObject->GetComponent<CTankTron>() != nullptr)
	{
		if (m_Health <= 0)
		{
			m_pPublisher->Notify(m_OwnerObject, Event::ActorDied);
			m_Health = 3;
			return;
		}
		m_pPublisher->Notify(m_OwnerObject, Event::ActorDamaged);
		return;
	}
	if (m_OwnerObject->GetComponent<CTankNPC>() != nullptr)
	{
		if (m_Health <= 0)
		{
			SceneManager::GetInstance().GetActiveScene()->RemoveObject(m_OwnerObject);
			m_pPublisher->Notify(m_OwnerObject, Event::NPCKilled);
			return;
		}
		m_pPublisher->Notify(m_OwnerObject, Event::NPCDamaged);
		return;
	}
}