#include "ChronosPCH.h"
#include "GameObject.h"
#include "CRender.h"
#include "Renderer.h"
#include "CTransform.h"
#include "Texture2D.h"

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
			if (m_ShouldRotate)
				Renderer::GetInstance().RenderTextureRotated(*m_Texture, pos.x, pos.y, m_Scale.x, m_Scale.y, m_RotationAngle, m_SourceRect);
			else
				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_Scale.x, m_Scale.y, m_SourceRect);
		}
		else
		{
			if (m_ShouldRotate)
				Renderer::GetInstance().RenderTextureRotated(*m_Texture, pos.x, pos.y, m_RotationAngle, m_SourceRect);
			else
				Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y, m_SourceRect);
		}
	}
}
void CRender::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}
void CRender::SetSourceRect(Rect rect)
{
	m_SourceRect = rect;
}
void CRender::RotateTexture(int angle)
{
	if(angle == 0)
	{
		m_ShouldRotate = false;
		m_RotationAngle = 0;
	}
	else
	{
		m_ShouldRotate = true;
		m_RotationAngle = angle;
	}
}