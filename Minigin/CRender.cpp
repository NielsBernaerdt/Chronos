#include "MiniginPCH.h"
#include "CRender.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "Transform.h"

CRender::CRender(std::shared_ptr<Texture2D> texture, Transform pos)
	: m_Texture{ texture }
	, m_Transform{ pos }
{
}
void CRender::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Transform.GetPosition();
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}
void CRender::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}
void CRender::SetPosition(Transform pos)
{
	m_Transform = pos;
}