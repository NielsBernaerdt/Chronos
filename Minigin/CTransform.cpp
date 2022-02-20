#include "MiniginPCH.h"
#include "CTransform.h"

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
const glm::vec3& CTransform::GetPosition() const
{
	return m_Transform;
}