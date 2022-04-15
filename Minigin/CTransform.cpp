#include "ChronosPCH.h"
#include "CTransform.h"

#include "GameObject.h"

CTransform::CTransform(GameObject* gameObject, int x, int y)
	: CBase(gameObject)
	, m_Transform{ x, y, 0 }
{
}
void CTransform::SetPosition(int x, int y)
{
	m_Transform.x = float(x);
	m_Transform.y = float(y);
}
const glm::vec3& CTransform::GetPosition()
{
	//if(m_OwnerObject->GetParent())
	//{
	//	m_WorldTransform = dynamic_cast<CTransform*>(m_OwnerObject->GetParent()->GetComponent<CTransform>().get())->GetPosition() + m_Transform;
	//}
	//else
	//{
	//	m_WorldTransform = m_Transform;
	//}
	//return m_WorldTransform;

	return m_Transform;
}