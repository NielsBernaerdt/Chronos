#include "InputCommands.h"
#include <GameObject.h>
#include <iostream>
#include "CTankTron.h"

//----------------------------------MOVERIGHT----------------------------------
MoveHorizontal::MoveHorizontal(bool moveRight)
	: BCommand()
	, m_DirectionValue(1)
	, m_IsPlayerPawn(false)
{
	if (moveRight == false)
		m_DirectionValue = -1;
}
MoveHorizontal::~MoveHorizontal()
{
}
void MoveHorizontal::Execute(GameObject* actor)
{
	if (m_CTron == nullptr)
	{
		if (!actor) return;
		if (actor->GetComponent<CTankTron>()) m_IsPlayerPawn = true;
		else m_IsPlayerPawn = false;
	}
	if (m_IsPlayerPawn == true)
	{
		if (m_CTron == nullptr)	m_CTron = dynamic_cast<CTankTron*>(actor->GetComponent<CTankTron>());
		m_CTron->MoveHorizontally(m_DirectionValue);
	}
}
//----------------------------------MOVERIGHT----------------------------------
MoveVertical::MoveVertical(bool moveUp)
	: BCommand()
	, m_DirectionValue(1)
	, m_IsPlayerPawn(false)
{
	if (moveUp == false)
		m_DirectionValue = -1;
}
MoveVertical::~MoveVertical()
{
}
void MoveVertical::Execute(GameObject* actor)
{
	if (m_CTron == nullptr)
	{
		if (!actor) return;
		if (actor->GetComponent<CTankTron>()) m_IsPlayerPawn = true;
		else m_IsPlayerPawn = false;
	}
	if (m_IsPlayerPawn == true)
	{
		if (m_CTron == nullptr)	m_CTron = dynamic_cast<CTankTron*>(actor->GetComponent<CTankTron>());
		m_CTron->MoveVertically(m_DirectionValue);
	}
}
//----------------------------------SHOOT----------------------------------
Shoot::Shoot()
	: BCommand()
	, m_IsPlayerPawn(false)
{
}
Shoot::~Shoot()
{
}
void Shoot::Execute(GameObject* actor)
{
	if (m_CTron == nullptr)
	{
		if (!actor) return;
		if (actor->GetComponent<CTankTron>()) m_IsPlayerPawn = true;
		else m_IsPlayerPawn = false;
	}
	if (m_IsPlayerPawn == true)
	{
		if (m_CTron == nullptr)	m_CTron = dynamic_cast<CTankTron*>(actor->GetComponent<CTankTron>());

		std::cout << "Mouse clicked\n";
	}
}