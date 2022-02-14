#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "CText.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"

CText::CText(const std::string& text, const std::shared_ptr<Font>& font) 
	: m_Text(text)
	, m_Font(font)
{
}

void CText::Update(float)
{
	const SDL_Color color = { 255,255,255 }; // only white text is supported now
	const auto surf = TTF_RenderText_Blended(m_Font->GetFont(), m_Text.c_str(), color);
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
}

void CText::SetText(const std::string& text)
{
	m_Text = text;
}
std::string CText::GetText() const
{
	return m_Text;
}