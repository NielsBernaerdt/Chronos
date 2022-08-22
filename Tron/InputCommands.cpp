#include "InputCommands.h"
#include <GameObject.h>
#include <iostream>
#include "CTankTron.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Tron.h"
#include "CRender.h"
#include "InputManager.h"

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
		AudioManager::GetInstance().PlaySound("AudioFiles/Shooting.wav", 15);
	}
}
//----------------------------------MoveBarrel----------------------------------
MoveBarrel::MoveBarrel(bool shouldTrackMouse)
	: BCommand()
	, m_IsPlayerPawn(false)
	, m_TracksMouse(shouldTrackMouse)
{
}
MoveBarrel::~MoveBarrel()
{
}
void MoveBarrel::Execute(GameObject* actor)
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

		if (actor->GetChildren().empty() == false)
		{
			if (m_TracksMouse) TrackMouse(actor);
			else TrackJoyStick(actor);
		}
	}
}
void MoveBarrel::TrackMouse(GameObject* actor)
{
	//LET BARREL ROTATE
	auto child = actor->GetChildren()[0];
	auto baseComp = child->GetComponent<CRender>();
	auto renderComp = dynamic_cast<CRender*>(baseComp);

	//MATH HERE//
	float angle{};
	glm::vec2 mousePos = InputManager::GetMousePos();

	mousePos.x -= actor->GetTransform()->GetPosition().x;
	mousePos.y -= actor->GetTransform()->GetPosition().y;

	//
	m_CTron->SetBarrelDirection({ mousePos.x, mousePos.y, 0 });
	//
	angle = atanf(mousePos.y / mousePos.x);
	angle = float(angle * 180 / 3.14159265358979323846264338327950288);
	if (mousePos.x < 0)
		angle += 180;
	renderComp->RotateTexture(int(angle));
}
void MoveBarrel::TrackJoyStick(GameObject* actor)
{
	//LET BARREL ROTATE
	auto child = actor->GetChildren()[0];
	auto baseComp = child->GetComponent<CRender>();
	auto renderComp = dynamic_cast<CRender*>(baseComp);

	//MATH HERE//
	float angle{};
	glm::vec2 mousePos = InputManager::GetJoyStickPos();

	//
	m_CTron->SetBarrelDirection({ mousePos.x, mousePos.y, 0 });
	//
	angle = atanf(-mousePos.y / mousePos.x);
	angle = float(angle * 180 / 3.14159265358979323846264338327950288);
	if (mousePos.x < 0)
		angle += 180;
	renderComp->RotateTexture(int(angle));
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