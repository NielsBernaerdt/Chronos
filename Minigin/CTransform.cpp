#include "MiniginPCH.h"
#include "CTransform.h"

CTransform::CTransform(std::shared_ptr<GameObject> gameObject, const Transform& pos)
	: CBase(gameObject)
	, m_Transform{ pos }
{
}
void CTransform::SetPosition(const Transform& pos)
{
	m_Transform = pos;
}
const Transform& CTransform::GetPosition() const
{
	return m_Transform;
}