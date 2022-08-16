#include "CHUDElement.h"
#include "GameObject.h"
#include "CText.h"
#include "CHealth.h"
#include "CPoints.h"

CHUDElement::CHUDElement(GameObject* gameObject, GameObject* objectToFollow)
	: CBase(gameObject)
	, m_pObjectToFollow(objectToFollow)
{
}

void CHUDElement::Initialize()
{
	m_pTextComponent = dynamic_cast<CText*>(m_OwnerObject->GetComponent<CText>());
	m_pHealthComponent = dynamic_cast<CHealth*>(m_pObjectToFollow->GetComponent<CHealth>());
	m_pPointsComponent = dynamic_cast<CPoints*>(m_pObjectToFollow->GetComponent<CPoints>());
}

void CHUDElement::Update(float)
{
	m_pTextComponent->SetText("Lives: " + std::to_string(m_pHealthComponent->GetHealth()) + "| Score: " + std::to_string(m_pPointsComponent->GetPoints()));
}