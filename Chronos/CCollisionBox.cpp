#include "ChronosPCH.h"
#include "CCollisionBox.h"

#include "CTransform.h"
#include "GameObject.h"

std::vector<CCollisionBox*> CCollisionBox::m_pCollisionBoxes;

CCollisionBox::CCollisionBox(GameObject* gameObject, Rect rect, bool enableOverlap)
	: CBase(gameObject)
	, m_Rect(rect)
	, m_IsOverlapEnabled(enableOverlap)
{
	m_pCollisionBoxes.push_back(this);
}
void CCollisionBox::Update(float)
{
	auto pos = m_OwnerObject->GetTransform()->GetPosition();
	m_Rect.left = (int)pos.x;
	m_Rect.bottom = (int)pos.y;

	if (m_IsOverlapEnabled)
	{
		for( const auto e : GetOverlappingObjects())
		{
			std::cout << e->GetName() << std::endl;
		}
	}
}


std::vector<GameObject*> CCollisionBox::GetOverlappingObjects()
{
	std::vector<GameObject*> temp;
	for (const auto e : m_pCollisionBoxes)
	{
		if (IsRectOverlapping(glm::vec2(m_Rect.left, m_Rect.bottom + m_Rect.height)
							, glm::vec2(m_Rect.left + m_Rect.width, m_Rect.bottom)
							, glm::vec2(e->m_Rect.left, e->m_Rect.bottom + e->m_Rect.height)
							, glm::vec2(e->m_Rect.left + e->m_Rect.width, e->m_Rect.bottom))
			&& e != this)
		{
			temp.push_back(e->m_OwnerObject);
		}
	}

	return temp;
}

bool CCollisionBox::IsRectOverlapping(glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 topLeft2, glm::vec2 bottomRight2)
{
    // If one rectangle is on left side of other
    if (topLeft.x > bottomRight2.x || topLeft2.x > bottomRight.x)
        return false;

    // If one rectangle is above other
    if (bottomRight.y > topLeft2.y || bottomRight2.y > topLeft.y)
        return false;

    return true;
}