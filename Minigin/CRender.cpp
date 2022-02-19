#include "MiniginPCH.h"
#include "CRender.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CTransform.h"

CRender::CRender(std::shared_ptr<GameObject> gameObject, std::shared_ptr<Texture2D> texture)
	: CBase (gameObject)
	, m_Texture{ texture }
{
	// need this in an initalization function
	//auto pos = dynamic_cast<CTransform>(m_OwnerObject->GetComponent<CTransform>());
	//m_Transform = pos;
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