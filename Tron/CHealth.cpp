#include "CHealth.h"
#include <GameObject.h>
#include <SceneManager.h>
#include "Scene.h"
#include "HighScore.h"
#include "CPoints.h"

void CHealth::SetHealth(int hp)
{
	m_Health = hp;
	if (m_Health <= 0)
	{
		//m_OwnerObject->Notify(m_OwnerObject, Event::ActorDied);
		SceneManager::GetInstance().GetActiveScene()->RemoveObject(m_OwnerObject);
	}
}

void CHealth::Damage()
{
	int points = dynamic_cast<CPoints*>(m_OwnerObject->GetComponent<CPoints>())->GetPoints();
	WriteScoreToFile(points);


	--m_Health;
	if(m_Health <= 0)
		SceneManager::GetInstance().GetActiveScene()->RemoveObject(m_OwnerObject);

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