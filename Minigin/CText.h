#pragma once
#include "CBase.h"

class Font;

class CText final : public CBase
{
public:
	CText(GameObject* gameObject, const std::string& text, int fontSize);
	~CText() override = default;
	CText(const CText& other) = delete;
	CText(CText&& other) = delete;
	CText& operator=(const CText& other) = delete;
	CText& operator=(CText&& other) = delete;

	void SetText(const std::string& text);
	const std::string& GetText() const;
	std::shared_ptr<Font> GetFont() const;
private:
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
};