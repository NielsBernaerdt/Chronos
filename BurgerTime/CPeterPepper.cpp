#include "CPeterPepper.h"

#include "CCollisionBox.h"
#include "CollisionGroups.h"
#include "CRender.h"
#include "GameObject.h"
#include "CTransform.h"
#include "PlayerState.h"
#include "Rect.h"

CPeterPepper::CPeterPepper(GameObject* gameObject)
	: CBase(gameObject)
{
	if (m_OwnerObject)
		m_PawnTransform = m_OwnerObject->GetTransform();
}
void CPeterPepper::Initialize()
{
	SetTexture();

	m_State = new IdleState{};
}
void CPeterPepper::Update(float deltaTime)
{
	//ANIMATION//
	m_AccTime += deltaTime;
	if (m_AccTime >= m_AnimationDuration
		&& (m_AccMovement.x != 0 || m_AccMovement.y !=0))
	{
		m_AccTime = 0.f;
		m_AnimationIndex = (m_AnimationIndex + 1) % 3;
		SetTexture();
	}
	//MOVEMENT//
	if (dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>().get())->GetOverlappingObjects(CollisionGroup::Ladder).size() == 0)
	{
		m_AccMovement.y = 0;
	}
	if (dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>().get())->GetOverlappingObjects(CollisionGroup::Ground).size() == 0)
	{
		m_AccMovement.x = 0;

		m_AccMovement.y += 400 * deltaTime;
	}
	m_PawnTransform->SetPosition(m_PawnTransform->GetPosition() + (m_AccMovement * deltaTime));
	m_AccMovement = { 0,0,0 };
	//STATES//
	PlayerState* state = m_State->Update(this->m_OwnerObject, this);
	if( state != nullptr)
	{
		delete m_State;
		m_State = state;
	}
}

void CPeterPepper::MoveHorizontally(int moveRight)
/**
 * moveRight = 1 to move right
 * moveLeft = -1 to move left
 */
{
	m_AccMovement.x += moveRight * m_MovSpeed;
}
void CPeterPepper::ClimbLadder(int moveUp)
/**
 * moveUp = 1 to move up
 * moveDown = -1 to move down
 */
{
	m_AccMovement.y -= moveUp * m_MovSpeed;
}

void CPeterPepper::SetTexture()
{
	glm::vec2 bottomLeft{};
	bottomLeft.x = float(m_AnimationIndex * m_SrcLength);
	bottomLeft.y = float(int(m_AnimSpriteRow) * m_SrcLength);
	Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SrcLength, m_SrcLength };

	dynamic_cast<CRender*>(m_OwnerObject->GetComponent<CRender>().get())->SetSourceRect(src);
}

void CPeterPepper::SetAnimSpriteRow(int rowNr)
{
	m_AnimSpriteRow = rowNr;
	SetTexture();
}