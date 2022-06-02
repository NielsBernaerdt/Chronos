#include "CPeterPepper.h"
#include "GameObject.h"
#include "CTransform.h"

CPeterPepper::CPeterPepper(GameObject* gameObject)
	: CBase(gameObject)
	, m_AccMovement()
{
	if (m_OwnerObject)
		m_PawnTransform = m_OwnerObject->GetTransform();
}
void CPeterPepper::Update(float deltaTime)
{
	m_PawnTransform->SetPosition(m_PawnTransform->GetPosition() + (m_AccMovement * deltaTime));
	m_AccMovement = { 0,0,0 };
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