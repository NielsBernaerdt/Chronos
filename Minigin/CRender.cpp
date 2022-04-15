#include "ChronosPCH.h"

#include "GameObject.h"
#include "CRender.h"
#include "Renderer.h"
#include "CTransform.h"

CRender::CRender(GameObject* gameObject, std::shared_ptr<Texture2D> texture)
	: CBase (gameObject)
	, m_Texture{ texture }
	, m_Transform{ 0,0,0 }
{
}
void CRender::Initialize()
{
	const auto pTransformComponent = std::dynamic_pointer_cast<CTransform>(m_OwnerObject->GetComponent<CTransform>());
	if (pTransformComponent == nullptr)
	{
		std::cout << "Text not valid\n";
	}
	else
	{
		m_Transform = pTransformComponent->GetPosition();
	}
}
void CRender::Render() const
{
	if (m_Texture != nullptr)
	{
		const auto& pos = m_Transform;
		Renderer::GetInstance().RenderTexture(*m_Texture, pos.x, pos.y);
	}
}
void CRender::SetTexture(std::shared_ptr<Texture2D> texture)
{
	m_Texture = texture;
}