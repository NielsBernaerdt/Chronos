#include "MiniginPCH.h"
#include <SDL_ttf.h>
#include "CText.h"
#include "Renderer.h"
#include "Font.h"
#include "Texture2D.h"
#include "ResourceManager.h"

CText::CText(std::shared_ptr<GameObject> gameObject, const std::string& text, int fontSize)
	: CBase(gameObject)
	, m_Text(text)
	, m_Font(ResourceManager::GetInstance().LoadFont("Lingua.otf", fontSize))
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