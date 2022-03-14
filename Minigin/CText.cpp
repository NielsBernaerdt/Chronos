#include "MiniginPCH.h"
#include "CText.h"
#include "Font.h"
#include "ResourceManager.h"

CText::CText(GameObject* gameObject, const std::string& text, int fontSize)
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