#include "CPlate.h"

#include "CBurgerIngredient.h"
#include "GameObject.h"
#include "CCollisionBox.h"
#include "CollisionGroups.h"

CPlate::CPlate(GameObject* gameObject, bool finalPlate)
	: CBase(gameObject)
	, m_IsFinalPlate{ finalPlate }
{
}

void CPlate::Initialize()
{
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>().get());
}
void CPlate::Update(float)
{
	if(m_pCollision->GetOverlappingObjects(CollisionGroup::Burger).size() >= 1)
	{
		dynamic_cast<CBurgerIngredient*>(m_pCollision->GetOverlappingObjects(CollisionGroup::Burger)[0]->GetComponent<CBurgerIngredient>().get())->StopMoving();
	}
}