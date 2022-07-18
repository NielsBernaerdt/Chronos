#include "CTankNPC.h"
#include <GameObject.h>
#include <CCollisionBox.h>

CTankNPC::CTankNPC(GameObject* gameObject, TankType type = TankType::BlueTank)
	: CBase(gameObject)
	, m_Type(type)
{
	if (m_OwnerObject)
		m_PawnTransform = m_OwnerObject->GetTransform();

	SetupTankType();
}

void CTankNPC::SetupTankType()
{
	switch (m_Type)
	{
	case TankType::BlueTank:
		m_MovSpeed = 200;
		m_PointsWorth = 100;
		break;
	case TankType::Recognizer:
		m_MovSpeed = 400;
		m_PointsWorth = 250;
		break;
	}
}

void CTankNPC::Initialize()
{
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
}

void CTankNPC::Update(float)
{
	
}