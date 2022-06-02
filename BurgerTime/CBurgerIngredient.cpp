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
	CCollisionBox* box = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>().get());
	for(const auto e : box->GetOverlappingObjects(CollisionGroup::Pawn))
	{
		std::cout << "Me, " << m_OwnerObject->GetName() << " touched " << e->GetName() << std::endl;
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