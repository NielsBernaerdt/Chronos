#include "ChronosPCH.h"

#include "GameObject.h"
#include "CRender.h"
#include "Renderer.h"
#include "CTransform.h"

CRender::CRender(GameObject* gameObject, std::shared_ptr<Texture2D> texture)
	: CBase (gameObject)
	, m_Texture{ texture }
{
}
void CRender::Initialize()
{
}
void CRender::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_OwnerObject->GetTransform()->GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}
void CRender::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}