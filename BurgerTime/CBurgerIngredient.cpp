#include "CBurgerIngredient.h"

#include "CCollisionBox.h"
#include "CollisionGroups.h"
#include "CRender.h"
#include "CTransform.h"
#include "GameObject.h"

CBurgerIngredient::CBurgerIngredient(GameObject* gameObject, Ingredient ingredient, int index)
	: CBase(gameObject)
	, m_Ingredient(ingredient)
	, m_Index(index)
{
}
void CBurgerIngredient::Initialize()
{
	SetTexture();

	glm::vec3 pos;
	pos.x += m_Index * m_OwnerObject->GetTransform()->GetScale().x;

	m_OwnerObject->GetTransform()->SetPosition(pos);
}
void CBurgerIngredient::Update(float)
{
	if (m_HasBeenTriggered == false)
	{
		CCollisionBox* box = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>().get());
		if (box->GetOverlappingObjects(CollisionGroup::Pawn).size() >= 1)
		{
			m_HasBeenTriggered = true;

			glm::vec3 pos{};
			pos.x += m_Index * m_OwnerObject->GetTransform()->GetScale().x;
			pos.y += m_OwnerObject->GetTransform()->GetScale().y / 2;

			m_OwnerObject->GetTransform()->SetPosition(pos);
		}
	}
}

void CBurgerIngredient::SetTexture()
{	
	glm::vec2 bottomLeft{};
	bottomLeft.x = float(m_Index * m_SideLength);
	bottomLeft.y = float(int(m_Ingredient) * m_SideLength);
	Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SideLength, m_SideLength };

	dynamic_cast<CRender*>(m_OwnerObject->GetComponent<CRender>().get())->SetSourceRect(src);
}