#include "ChronosPCH.h"

#include "GameObject.h"
#include "CRender.h"
#include "Renderer.h"
#include "CTransform.h"

CRender::CRender(GameObject* gameObject, std::shared_ptr<Texture2D> texture, bool scaleToObject)
	: CBase (gameObject)
	, m_Texture{ texture }
	, m_ScaleToObject{scaleToObject}
{
}
void CRender::Initialize()
{
	m_Scale = m_OwnerObject->GetTransform()->GetScale();
}
void CRender::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_OwnerObject->GetTransform()->GetPosition();
		if (m_ScaleToObject)
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Scale.x, m_Scale.y);
		}
		else
		{
			Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
		}
	}
}
void CRender::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}