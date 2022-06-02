#include "CPeterPepper.h"

#include "CRender.h"
#include "GameObject.h"
#include "CTransform.h"
#include "Rect.h"

CPeterPepper::CPeterPepper(GameObject* gameObject)
	: CBase(gameObject)
	, m_AccMovement()
{
	if (m_OwnerObject)
		m_PawnTransform = m_OwnerObject->GetTransform();
}
void CPeterPepper::Initialize()
{
	SetTexture();
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

void CPeterPepper::SetTexture()
{
	glm::vec2 bottomLeft{};
	bottomLeft.x = float(m_AnimationIndex * m_SrcLength);
	bottomLeft.y = float(int(m_CurrentState) * m_SrcLength);
	Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SrcLength, m_SrcLength };

	dynamic_cast<CRender*>(m_OwnerObject->GetComponent<CRender>().get())->SetSourceRect(src);
}