#include "CMrHotDog.h"
#include "CBurgerIngredient.h"
#include "GameObject.h"
#include "PlayerState.h"
#include "CCollisionBox.h"
#include "CHealth.h"
#include "CollisionGroups.h"
#include "CRender.h"

CMrHotDog::CMrHotDog(GameObject* gameObject)
	: CBase(gameObject)
{
}
CMrHotDog::~CMrHotDog()
{
}

void CMrHotDog::Initialize()
{
	SetTexture();
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
}
void CMrHotDog::Update(float deltaTime)
{
	//ANIMATION//
	m_AccTime += deltaTime;
	if (m_AccTime >= m_AnimationDuration)
	{
		m_AccTime = 0.f;
		m_AnimationIndex = (m_AnimationIndex + 1) % 3;
		SetTexture();
	}


	//MOVEMENT//
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Ladder).size() == 0)
	{
		m_AccMovement.y = 0;
	}
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Ground).size() == 0)
	{
		m_AccMovement.x = 0;
	}

	//PLAYER//
	DamagePlayer();

	//BURGERS
	BurgerCollision();
}

void CMrHotDog::SetTexture()
{
	glm::vec2 bottomLeft{};
	bottomLeft.x = float(m_AnimationIndex * m_SrcLength);
	bottomLeft.y = float(int(m_AnimSpriteRow) * m_SrcLength);
	Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SrcLength, m_SrcLength };

	dynamic_cast<CRender*>(m_OwnerObject->GetComponent<CRender>())->SetSourceRect(src);
}

void CMrHotDog::DamagePlayer()
{
	auto playerVector = m_pCollision->GetOverlappingObjects(CollisionGroup::Pawn);
	if (playerVector.size() >= 1)
	{
		for(const auto& player : playerVector)
		{
			dynamic_cast<CHealth*>(player->GetComponent<CHealth>())->Damage();
		}
	}
}

void CMrHotDog::BurgerCollision()
{
	auto burgerVector = m_pCollision->GetOverlappingObjects(CollisionGroup::Burger);
	if (burgerVector.size() >= 1)
	{
		for(const auto& burger : burgerVector)
		{
			if(dynamic_cast<CBurgerIngredient*>(burger->GetParent()->GetComponent<CBurgerIngredient>())->IsOnPlate() == false)
			{
				dynamic_cast<CHealth*>(m_OwnerObject->GetComponent<CHealth>())->Damage();
			}
		}
	}
}