#include "PlayerState.h"
#include "GameObject.h"
#include "CPeterPepper.h"
#include "CCollisionBox.h"
#include "CollisionGroups.h"

//#define SHOW_DEBUG

PlayerState* IdleState::Update(GameObject* pPawn, CPeterPepper*)
{
	#ifdef  SHOW_DEBUG
	std::cout << "Idle State\n";
#endif

	if (m_DoOnce)
	{
		m_DoOnce = false;
		m_PrevPos = pPawn->GetTransform()->GetPosition();
		return nullptr;
	}

	if(m_PrevPos != pPawn->GetTransform()->GetPosition())
	{

		return new WalkingState{};
	}
	m_PrevPos = pPawn->GetTransform()->GetPosition();
	return nullptr;
}

PlayerState* WalkingState::Update(GameObject* pPawn, CPeterPepper* pPeter)
{
#ifdef SHOW_DEBUG
	std::cout << "Walking State\n";
#endif

	if (m_DoOnce)
	{
		m_DoOnce = false;
		m_PrevPos = pPawn->GetTransform()->GetPosition();

		m_pCollision = dynamic_cast<CCollisionBox*>(pPawn->GetComponent<CCollisionBox>());

		return nullptr;
	}
	if(m_pCollision->GetOverlappingObjects(CollisionGroup::Ladder).size() >= 1
		//&& m_pCollision->GetOverlappingObjects(CollisionGroup::Ground).size() < 1
		&& pPeter->GetAccMovement().y != 0
		)
	{
		pPeter->SetAnimSpriteRow(2);
		return new ClimbingState{};
	}
	if (m_PrevPos == pPawn->GetTransform()->GetPosition())
	{
		return new IdleState{};
	}
	m_PrevPos = pPawn->GetTransform()->GetPosition();
	return nullptr;
}

PlayerState* ClimbingState::Update(GameObject* pPawn, CPeterPepper* pPeter)
{
#ifdef SHOW_DEBUG
	std::cout << "Climbing\n";
#endif

	if (m_DoOnce)
	{
		m_DoOnce = false;
		m_pCollision = dynamic_cast<CCollisionBox*>(pPawn->GetComponent<CCollisionBox>());

		return nullptr;
	}
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Ladder).size() >= 1
		&& m_pCollision->GetOverlappingObjects(CollisionGroup::Ground).size() > 0
		&& pPeter->GetAccMovement().y == 0
		)
	{
		pPeter->SetAnimSpriteRow(0);
		return new IdleState{};
	}

	if(pPeter->GetAccMovement().y >= 0)
	{
		pPeter->SetAnimSpriteRow(1);
	}
	else
	{
		pPeter->SetAnimSpriteRow(2);
	}

	return nullptr;
}
