#include "CBullet.h"
#include <CCollisionBox.h>
#include "CollisionGroups.h"
#include <GameObject.h>
#include <iostream>
#include "CHealth.h"
#include "Scene.h"
#include "SceneManager.h"

CBullet::CBullet(GameObject* pGameObject, glm::vec3 velocity, CollisionGroup collisionGroup)
	: CBase(pGameObject)
	, m_Velocity(velocity * m_VelocityMultiplier)
	, m_OwnerCollision(collisionGroup)
{
	if (m_OwnerObject)
		m_pPawnTransform = m_OwnerObject->GetTransform();

	m_Velocity *= m_BulletSpeed;
}
void CBullet::Initialize()
{
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
}

void CBullet::Update(float deltaTime)
{
	//MOVEMENT//
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall).empty() == false)
	{
		m_pPawnTransform->SetPosition(m_PrevPosition);

		if (m_NrBounces < m_MaxNrBounces)
		{
			BounceBullet();
			++m_NrBounces;
		}
		else
		{
			SceneManager::GetInstance().GetActiveScene()->RemoveObject(m_OwnerObject);
		}
	}
	else
	{
		m_PrevPosition = m_pPawnTransform->GetPosition();
		m_pPawnTransform->SetPosition(m_pPawnTransform->GetPosition() + (m_Velocity * deltaTime));
	}
	//Enemy Hit//
	auto enemies = m_pCollision->GetOverlappingObjects(CollisionGroup::NPC);
	if (enemies.empty() == false)
	{
		for(const auto& e : enemies)
		{
			if (m_OwnerCollision != CollisionGroup::NPC)
			{
				dynamic_cast<CHealth*>(e->GetComponent<CHealth>())->Damage();
				SceneManager::GetInstance().GetActiveScene()->RemoveObject(m_OwnerObject);
				return;
			}
		}
	}
	//Player Hit//
	auto players = m_pCollision->GetOverlappingObjects(CollisionGroup::Pawn);
	if (players.empty() == false)
	{
		for (const auto& e : players)
		{
			if (m_OwnerCollision != CollisionGroup::Pawn)
			{
				//TP player
				e->GetTransform()->SetPosition(23, 65);
				dynamic_cast<CHealth*>(e->GetComponent<CHealth>())->Damage();
				SceneManager::GetInstance().GetActiveScene()->RemoveObject(m_OwnerObject);
				return;
			}
		}
	}
}

void CBullet::BounceBullet()
{
	auto pos = m_OwnerObject->GetTransform()->GetPosition();
	auto wall = m_pCollision->GetOverlappingObjects(CollisionGroup::Wall)[0];
	Rect wallRect = {
		static_cast<int>(wall->GetTransform()->GetPosition().x)
		, static_cast<int>(wall->GetTransform()->GetPosition().y)
		, static_cast<int>(wall->GetTransform()->GetScale().x)
		, static_cast<int>(wall->GetTransform()->GetScale().y)
	};
	// If above or below the wall -> bounce off vertically
	if(pos.y - (wallRect.bottom + wallRect.height) >= 0
		|| wallRect.bottom - pos.y >= 0)
	{
		m_Velocity.y *= -1;
	}
	// If left or right of the wall -> bounce off horizontally
	if (wallRect.left - pos.x >= 0
		|| pos.x - (wallRect.left + wallRect.width) >= 0)
	{
		m_Velocity.x *= -1;
	}
}