#pragma once
#include "CBase.h"
#include "Transform.h"

class Font;

class CText final : public CBase
{
public:
	explicit CText(const std::string& text, const std::shared_ptr<Font>& font);
	virtual ~CText() = default;
	CText(const CText& other) = delete;
	CText(CText&& other) = delete;
	CText& operator=(const CText& other) = delete;
	CText& operator=(CText&& other) = delete;

	void Update(float deltaTime) override;
	void SetText(const std::string& text);
	std::string GetText() const;
private:
	std::string m_Text;
	std::shared_ptr<Font> m_Font;
};