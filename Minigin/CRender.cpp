#include "MiniginPCH.h"
#include <SDL_ttf.h>

#include "CRender.h"
#include "Texture2D.h"
#include "Renderer.h"
#include "GameObject.h"
#include "CTransform.h"
#include "Font.h"

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
	//
	const auto pTextComponent = std::dynamic_pointer_cast<CText>(m_OwnerObject->GetComponent<CText>());
	if (pTextComponent != nullptr)
	{
		const auto surf = TTF_RenderText_Blended(
			pTextComponent->GetFont()->GetFont()
			, pTextComponent->GetText().c_str()
			, SDL_Color{ 255,255,255 });
		if (surf == nullptr)
		{
			throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());
		}
		auto texture = SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surf);
		if (texture == nullptr)
		{
			throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());
		}
		SDL_FreeSurface(surf);

		SetTexture(std::make_shared<Texture2D>(texture));
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