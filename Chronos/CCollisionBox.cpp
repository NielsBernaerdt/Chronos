#include "ChronosPCH.h"
#include "CCollisionBox.h"
#include "GameObject.h"
#include "Scene.h"
#include "SceneManager.h"

std::map<CCollisionBox*, int> CCollisionBox::m_pCollisionBoxes;
//std::vector<CCollisionBox*> CCollisionBox::m_pCollisionBoxes;

CCollisionBox::CCollisionBox(GameObject* gameObject, CollisionGroup group, bool useScale, Rect sizeRect)
	: CBase(gameObject)
	, m_CollisionGroup(group)
	, m_UseScale(useScale)
	, m_Rect(sizeRect)
{
	//m_pCollisionBoxes.push_back(this);
	m_pCollisionBoxes.insert(std::make_pair<>(this, 0));
}
void CCollisionBox::Initialize()
{
	auto pos = m_OwnerObject->GetTransform()->GetPosition();

	m_Rect.left += (int)pos.x;
	m_Rect.bottom += (int)pos.y;
	if (m_UseScale)
	{
		auto scale = m_OwnerObject->GetTransform()->GetScale();
		m_Rect.width = (int)scale.x;
		m_Rect.height = (int)scale.y;
	}
}
void CCollisionBox::Update(float)
{
	auto pos = m_OwnerObject->GetTransform()->GetPosition();
	m_Rect.left = (int)pos.x;
	m_Rect.bottom = (int)pos.y;
}


std::vector<GameObject*> CCollisionBox::GetOverlappingObjects(CollisionGroup filter) const
{
	std::vector<GameObject*> temp;
	for (const auto e : m_pCollisionBoxes)
	{
		if (e.second != SceneManager::GetInstance().GetActiveScene()
			|| e.first->m_CollisionGroup != filter) continue;

		if (IsRectOverlapping(glm::vec2(m_Rect.left, m_Rect.bottom + m_Rect.height)
			, glm::vec2(m_Rect.left + m_Rect.width, m_Rect.bottom)
			, glm::vec2(e.first->m_Rect.left, e.first->m_Rect.bottom + e.first->m_Rect.height)
			, glm::vec2(e.first->m_Rect.left + e.first->m_Rect.width, e.first->m_Rect.bottom))
			&& e.first != this)
		{
			temp.push_back(e.first->m_OwnerObject);
		}
	}

	return temp;
}

bool CCollisionBox::IsRectOverlapping(glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 topLeft2, glm::vec2 bottomRight2) const
{
    // If one rectangle is on left||right side of other
    if (topLeft.x > bottomRight2.x || topLeft2.x > bottomRight.x)
        return false;

    // If one rectangle is above||below other
    if (bottomRight.y > topLeft2.y || bottomRight2.y > topLeft.y)
        return false;

    return true;
}