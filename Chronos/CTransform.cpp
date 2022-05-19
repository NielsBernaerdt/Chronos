#include "ChronosPCH.h"
#include "CTransform.h"

#include "GameObject.h"

CTransform::CTransform(GameObject* gameObject, int x, int y)
	: CBase(gameObject)
	, m_Pos{ x, y, 0 }
{
}
void CTransform::SetPosition(int x, int y)
{
	m_IsDirty = true;

	m_Pos.x = float(x);
	m_Pos.y = float(y);
}
const glm::vec3& CTransform::GetPosition()
{
	if(m_IsDirty == true)
	{
		UpdateRelativeTransform();
	}

	return m_WorldPos;
}
void CTransform:: UpdateRelativeTransform()
{
	m_IsDirty = false;
	std::cout << m_OwnerObject->GetName() << "; " << "Hai\n";

	if (m_OwnerObject->GetParent() != nullptr)
	{
		m_WorldPos = m_OwnerObject->GetParent()->GetTransform()->GetPosition() + m_Pos;
	}
	else
	{
		m_WorldPos = m_Pos;
	}

	for(const auto child : m_OwnerObject->GetChildren())
	{
		CTransform* childCTransform = child->GetTransform();
		if (childCTransform->IsDirty())
		{
			childCTransform->UpdateRelativeTransform();
		}
	}
}