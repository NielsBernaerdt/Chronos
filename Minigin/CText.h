#pragma once
#include "CBase.h"

class Font;
class CRender;

class CText final : public CBase
{
public:
	CText(GameObject* gameObject = nullptr
		, const std::string& text = "Default Text"
		, int fontSize = 18
		, SDL_Color color = SDL_Color{255, 255, 255});
	~CText() override = default;
	CText(const CText& other) = delete;
	CText(CText&& other) = delete;
	CText& operator=(const CText& other) = delete;
	CText& operator=(CText&& other) = delete;

	void SetText(const std::string& text);
	const std::string& GetText() const;
	std::shared_ptr<Font> GetFont() const;

	void SetColor(const SDL_Color& color);

	void Initialize() override;
	void Update(float) override;

private:
	std::string m_Text{};
	std::shared_ptr<Font> m_Font{};
	SDL_Color m_Color{};

	std::shared_ptr<CRender> m_pRenderComponent{};
};