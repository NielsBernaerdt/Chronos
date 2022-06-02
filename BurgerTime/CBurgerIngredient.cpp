#include "CBurgerIngredient.h"

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
	if(m_Index % 2 == 0)
	{
		m_Up = 1;
	}
	else
	{
		m_Up = -1;
	}
}
void CBurgerIngredient::Update(float deltaTime)
{
	m_accTime += deltaTime;

	if(m_accTime >= 0.5f)
	{
		m_accTime = 0.f;

		m_Up *= -1;

		glm::vec3 pos;
		pos.x += m_Index * 10 * m_Diff;
		pos.y += m_Diff * m_Up;
		
		m_OwnerObject->GetTransform()->SetPosition(pos);
	}
}