#include "ChronosPCH.h"
#include "CText.h"

#include "GameObject.h"
#include <SDL_ttf.h>
#include "ResourceManager.h"
#include "Font.h"
#include "Renderer.h"
#include "CRender.h"
#include "Texture2D.h"

CText::CText(GameObject* gameObject, const std::string& text, int fontSize, SDL_Color color, bool renderText)
	: CBase(gameObject)
	, m_Text(text)
	, m_Font(ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize))
	, m_Color(color)
	, m_RenderText(renderText)
{
}

void CText::SetText(const std::string& text)
{
	m_Text = text;
}
const std::string& CText::GetText() const
{
	return m_Text;
}

std::shared_ptr<Font> CText::GetFont() const
{
	return m_Font;
}

void CText::SetColor(const SDL_Color& color)
{
	m_Color = color;
}

void CText::Initialize()
{
	if (m_RenderText == false)
		return;

	m_pRenderComponent = std::dynamic_pointer_cast<CRender>(m_OwnerObject->GetComponent<CRender>());
	if (m_pRenderComponent == nullptr)
	{
		std::cout << "RenderComponent not valid\n";
	}
}

void CText::Update(float)
{
	//Check for valid rendercomponent
	if(!m_pRenderComponent)
	{
		return;
	}
	//set texture of render comp
	const auto surf = TTF_RenderText_Blended(
		m_Font->GetFont()
		, m_Text.c_str()
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

	m_pRenderComponent->SetTexture(std::make_shared<Texture2D>(texture));
}
