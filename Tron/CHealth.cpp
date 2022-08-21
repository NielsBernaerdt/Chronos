#include "CHealth.h"
#include <GameObject.h>
#include <SceneManager.h>
#include "Scene.h"
#include "CPoints.h"
#include "BPublisher.h"
#include "BObserver.h"
#include "CTankNPC.h"

void CHealth::SetHealth(int hp)
{
	m_Health = hp;
}

void CHealth::Damage()
{
	--m_Health;
	if (m_pPublisher)
	{
		m_pPublisher->Notify(m_OwnerObject, Event::ActorDamaged);
	}
	if (m_Health <= 0)
	{
		SceneManager::GetInstance().GetActiveScene()->RemoveObject(m_OwnerObject);
		m_pPublisher->Notify(m_OwnerObject, Event::ActorDied);
	}

	//auto peterComp = dynamic_cast<CPeterPepper*>(m_OwnerObject->GetComponent<CPeterPepper>());
	//if (peterComp != nullptr)
	//{
	//	m_OwnerObject->GetTransform()->SetPosition(590, 35);

	//	if (m_Health == 0)
	//	{
	//		m_OwnerObject->Notify(m_OwnerObject, Event::ActorDied);
	//	}
	//	else
	//	{
	//		m_OwnerObject->Notify(m_OwnerObject, Event::ActorDamaged);
	//	}
	//}
	//else
	//{
	//	auto hotdogComp = dynamic_cast<CMrHotDog*>(m_OwnerObject->GetComponent<CMrHotDog>());
	//	if (hotdogComp != nullptr)
	//	{
	//		m_OwnerObject->GetTransform()->SetPosition(-200, -200);

	//		if (m_Health == 0)
	//		{
	//			m_OwnerObject->Notify(m_OwnerObject, Event::NPCKilled);
	//		}
	//	}
	//}
}