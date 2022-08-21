#include "InputCommands.h"
#include <GameObject.h>
#include <iostream>
#include "CTankTron.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Tron.h"

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

		m_CTron->Shoot();
	}
}
//----------------------------------OPENSCENE----------------------------------
OpenScene::OpenScene(int sceneIdx)
	: BCommand()
	, m_SceneIndex(sceneIdx)
{
}
OpenScene::~OpenScene()
{
}
void OpenScene::Execute(GameObject*)
{
	SceneManager::GetInstance().OpenScene(m_SceneIndex);
	SceneManager::GetInstance().GetScene(m_SceneIndex)->ClearScene();
	Tron::LoadSceneByIndex(m_SceneIndex);
}
//----------------------------------RESETSCENE----------------------------------
ResetScene::ResetScene()
	: BCommand()
{
}
ResetScene::~ResetScene()
{
}
void ResetScene::Execute(GameObject* )
{
	SceneManager::GetInstance().GetActiveScene()->ClearScene();
	Tron::LoadSceneByIndex(SceneManager::GetInstance().GetActiveSceneIdx());
}