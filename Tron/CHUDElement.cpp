#include "CHUDElement.h"
#include "GameObject.h"
#include "CText.h"
#include "CHealth.h"
#include "CPoints.h"

CHUDElement::CHUDElement(GameObject* pGameObject, GameObject* pPawnOne, GameObject* pPawnTwo)
	: CBase(pGameObject)
	, m_PlayerOnePawn(pPawnOne)
	, m_PlayerTwoPawn(pPawnTwo)
{
}

void CHUDElement::Initialize()
{
	m_pTextComponent = dynamic_cast<CText*>(m_OwnerObject->GetComponent<CText>());
	m_pHealthComponentOne = dynamic_cast<CHealth*>(m_PlayerOnePawn->GetComponent<CHealth>());
	m_pPointsComponentOne = dynamic_cast<CPoints*>(m_PlayerOnePawn->GetComponent<CPoints>());
	if (m_PlayerTwoPawn)
	{
		m_pHealthComponentTwo = dynamic_cast<CHealth*>(m_PlayerTwoPawn->GetComponent<CHealth>());
		m_pPointsComponentTwo = dynamic_cast<CPoints*>(m_PlayerTwoPawn->GetComponent<CPoints>());
	}
}

void CHUDElement::Update(float)
{
	std::string displayedText{ "Lives: " + std::to_string(m_pHealthComponentOne->GetHealth()) };
	if (m_PlayerTwoPawn)
		displayedText += " | Lives: " + std::to_string(m_pHealthComponentTwo->GetHealth());
	else
		displayedText += " | Score: " + std::to_string(m_pPointsComponentOne->GetPoints());

	m_pTextComponent->SetText(displayedText);
}