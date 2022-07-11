#include "CBullet.h"
#include <CCollisionBox.h>
#include "CollisionGroups.h"
#include <GameObject.h>

CBullet::CBullet(GameObject* gameObject)
	: CBase(gameObject)
{
	if (m_OwnerObject)
		m_PawnTransform = m_OwnerObject->GetTransform();
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
		m_PawnTransform->SetPosition(m_PrevPosition);
	}
	else
	{
		m_PrevPosition = m_PawnTransform->GetPosition();
		m_PawnTransform->SetPosition(m_PawnTransform->GetPosition() + (m_Velocity * deltaTime));
	}

	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall).empty() == false)
	{
		++m_NrBounces;
		BounceBullet();
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