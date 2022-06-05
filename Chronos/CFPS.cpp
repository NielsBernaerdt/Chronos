#include "ChronosPCH.h"
#include "CFPS.h"
#include "GameObject.h"
#include "CText.h"

CFPS::CFPS(GameObject* gameObject)
	: CBase(gameObject)
{
}

void CFPS::Initialize()
{
	m_pTextComponent = dynamic_cast<CText*>(m_OwnerObject->GetComponent<CText>());
	if (m_pTextComponent == nullptr)
	{
		std::cout << "TextCompnent not valid\n";
	}
}

void CFPS::Update(float deltaTime)
{
	const int fps = static_cast<int>(1 / deltaTime);
	m_AccTime += deltaTime;
	if (m_FirstUpdate)
	{
		m_PreviousFPS = fps;
		m_FirstUpdate = false;
		return;
	}
	if ( m_pTextComponent
		&& fps != m_PreviousFPS
		&& m_Interval - m_AccTime <= 0.f)
	{
		m_AccTime = 0;
		m_PreviousFPS = fps;
		m_pTextComponent->SetText(std::to_string(fps));
	}
}