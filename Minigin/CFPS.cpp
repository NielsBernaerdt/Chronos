#include "MiniginPCH.h"
#include <SDL_ttf.h>

#include "CFPS.h"
#include "GameObject.h"
#include "CText.h"
#include "CRender.h"
#include "Font.h"
#include "Renderer.h"
#include "Texture2D.h"

CFPS::CFPS(std::shared_ptr<GameObject> gameObject)
	: CBase(gameObject)
{
}

void CFPS::Initialize()
{
	//Get components through owner object
	m_pTextComponent = std::dynamic_pointer_cast<CText>(m_OwnerObject->GetComponent<CText>());
	if (m_pTextComponent == nullptr)
	{
		std::cout << "Text not valid\n";
	}
	m_pRenderComponent = std::dynamic_pointer_cast<CRender>(m_OwnerObject->GetComponent<CRender>());
	if (m_pRenderComponent == nullptr)
	{
		std::cout << "Render not valid\n";
	}
	//set text of component to current fps
	m_pTextComponent->SetText("144 fps jippie");
}

void CFPS::Update(float deltaTime)
{
	//Set Text to current FPS
	int fps = int(1.0f / deltaTime);
	m_pTextComponent->SetText(std::to_string(fps));
	//set texture of render comp using this newly updated fps text
	const auto surf = TTF_RenderText_Blended(
											m_pTextComponent->GetFont()->GetFont()
											, m_pTextComponent->GetText().c_str()
											, SDL_Color { 255,255,255 });
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