#include "CEnemyPlayer.h"

#include <iostream>

#include "CBurgerIngredient.h"
#include "CCollisionBox.h"
#include "CollisionGroups.h"
#include "CRender.h"
#include "CHealth.h"
#include "GameObject.h"

CEnemyPlayer::CEnemyPlayer(GameObject* gameObject)
	: CBase(gameObject)
{
	if (m_OwnerObject)
		m_PawnTransform = m_OwnerObject->GetTransform();
}
CEnemyPlayer::~CEnemyPlayer()
{
	delete m_State;
	m_State = nullptr;
}

void CEnemyPlayer::Initialize()
{
	SetTexture();
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
	m_State = new IdleState{};
}
void CEnemyPlayer::Update(float deltaTime)
{

	//ANIMATION//
	m_AccTime += deltaTime;
	if (m_AccTime >= m_AnimationDuration
		&& (m_AccMovement.x != 0 || m_AccMovement.y != 0))
	{
		m_AccTime = 0.f;
		m_AnimationIndex = (m_AnimationIndex + 1) % 3;
		SetTexture();
	}
	
	//PLAYER//
	DamagePlayer();

	//BURGERS
	BurgerCollision();

	//MOVEMENT//
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Ladder).size() == 0)
	{
		m_AccMovement.y = 0;
	}
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Ground).size() == 0)
	{
		m_AccMovement.x = 0;
	}


	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Ladder).size() < 1
		&& m_pCollision->GetOverlappingObjects(CollisionGroup::Ground).size() < 1)
	{
		m_PawnTransform->SetPosition(m_PrevPosition);
	}

	m_PrevPosition = m_PawnTransform->GetPosition();
	m_PawnTransform->SetPosition(m_PawnTransform->GetPosition() + (m_AccMovement * deltaTime));
	m_AccMovement = { 0,0,0 };
}

void CEnemyPlayer::MoveHorizontally(int moveRight)
/**
 * moveRight = 1 to move right
 * moveLeft = -1 to move left
 */
{
	m_AccMovement.x += moveRight * m_MovSpeed;
}
void CEnemyPlayer::ClimbLadder(int moveUp)
/**
 * moveUp = 1 to move up
 * moveDown = -1 to move down
 */
{
	m_AccMovement.y -= moveUp * m_MovSpeed;
}

void CEnemyPlayer::SetTexture()
{
	glm::vec2 bottomLeft{};
	bottomLeft.x = float(m_AnimationIndex * m_SrcLength);
	bottomLeft.y = float(int(m_AnimSpriteRow) * m_SrcLength);
	Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SrcLength, m_SrcLength };

	dynamic_cast<CRender*>(m_OwnerObject->GetComponent<CRender>())->SetSourceRect(src);
}

void CEnemyPlayer::DamagePlayer()
{
	auto playerVector = m_pCollision->GetOverlappingObjects(CollisionGroup::Pawn);
	if (playerVector.size() >= 1)
	{
		for (const auto& player : playerVector)
		{
			dynamic_cast<CHealth*>(player->GetComponent<CHealth>())->Damage();
		}
	}
}

void CEnemyPlayer::BurgerCollision()
{
	auto burgerVector = m_pCollision->GetOverlappingObjects(CollisionGroup::Burger);
	if (burgerVector.size() >= 1)
	{
		for (const auto& burger : burgerVector)
		{
			if (dynamic_cast<CBurgerIngredient*>(burger->GetParent()->GetComponent<CBurgerIngredient>())->IsOnPlate() == false)
			{
				std::cout << "Noooooo\n";
				dynamic_cast<CHealth*>(m_OwnerObject->GetComponent<CHealth>())->Damage();
			}
		}
	}
}