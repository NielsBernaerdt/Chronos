#include "CTankTron.h"
#include <GameObject.h>
#include <CCollisionBox.h>
#include <CRender.h>
#include <iostream>
#include "CollisionGroups.h"
#include "InputManager.h"
#include "PlayerState.h"
//SPAWN BULLET
#include "ResourceManager.h"
#include "CBullet.h"
#include "Scene.h"
#include "SceneManager.h"
#include <AudioManager.h>

CTankTron::CTankTron(GameObject* pGameObject)
	: CBase(pGameObject)
{
	if (m_OwnerObject)
		m_pPawnTransform = m_OwnerObject->GetTransform();
	SetTexture();
}

CTankTron::~CTankTron()
{
	delete m_pState;
	m_pState = nullptr;
}

void CTankTron::Initialize()
{
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
	m_BulletCollisionGroup = m_pCollision->GetCollisionGroup();

	m_pState = new IdleState{};
}
void CTankTron::Update(float deltaTime)
{
	m_AccTimeShooting += deltaTime;
	//STATES//
	PlayerState* state = m_pState->Update(this->m_OwnerObject, this);
	if (state != nullptr)
	{
		delete m_pState;
		m_pState = state;
	}

	//MOVEMENT// 
	if (m_IgnoreWalls)
	{
		const auto newPos = m_pPawnTransform->GetPosition() + m_AccMovement * deltaTime;
		m_pPawnTransform->SetPosition(newPos);
	}
	else
	{
		const auto newPosY = m_pPawnTransform->GetPosition() + glm::vec3{ 0, m_AccMovement.y, 0 } *deltaTime;
		const Rect newRectY{ (int)newPosY.x, (int)newPosY.y, (int)m_pPawnTransform->GetScale().x, (int)m_pPawnTransform->GetScale().y };
		if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall, newRectY).empty())
		{
			m_PrevPosition = m_pPawnTransform->GetPosition();
			m_pPawnTransform->SetPosition(newPosY);
		}
		const auto newPosX = m_pPawnTransform->GetPosition() + glm::vec3{ m_AccMovement.x, 0, 0 } *deltaTime;
		const Rect newRectX{ (int)newPosX.x, (int)newPosX.y, (int)m_pPawnTransform->GetScale().x, (int)m_pPawnTransform->GetScale().y };
		if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall, newRectX).empty())
		{
			m_PrevPosition = m_pPawnTransform->GetPosition();
			m_pPawnTransform->SetPosition(newPosX);
		}
	}
	m_AccMovement = { 0, 0, 0 };
}

void CTankTron::MoveHorizontally(int moveRight)
/**
 * moveRight = 1 to move right
 * moveLeft = -1 to move left
 */
{
	m_AccMovement.x += moveRight * m_MovSpeed;
}
void CTankTron::MoveVertically(int moveUp)
/**
 * moveUp = 1 to move up
 * moveDown = -1 to move down
 */
{
	m_AccMovement.y -= moveUp * m_MovSpeed;
}

void CTankTron::Shoot()
{
	if (m_AccTimeShooting <= m_ShootingCooldown)
		return;
	m_AccTimeShooting = 0.f;
	AudioManager::GetInstance().PlaySound("AudioFiles/Shooting.wav", 15);

	const auto bullet = std::make_shared<GameObject>(std::string{ "bullet" });
	auto startingPos = m_OwnerObject->GetTransform()->GetPosition();
	startingPos.x += 15;
	startingPos.y += 15;
	bullet->GetTransform()->SetPosition(startingPos);
	bullet->GetTransform()->SetScale(10, 10);

	const auto bulletTexture = ResourceManager::GetInstance().LoadTexture("Tron/Bullet.png");
	std::unique_ptr<CRender> bulletCRender = std::make_unique<CRender>(bullet.get(), bulletTexture, true);
	bullet->AddComponent(std::move(bulletCRender));

	std::unique_ptr<CCollisionBox> bulletCCollision = std::make_unique<CCollisionBox>(bullet.get(), CollisionGroup::Bullet);
	bullet->AddComponent(std::move(bulletCCollision));

	std::unique_ptr<CBullet> bulletCBullet = std::make_unique<CBullet>(bullet.get(), glm::normalize(m_BarrelDirection), m_BulletCollisionGroup);
	bullet->AddComponent(std::move(bulletCBullet));

	SceneManager::GetInstance().GetActiveScene()->SpawnObject(bullet);
}

void CTankTron::SetTexture()
{
	glm::vec2 bottomLeft{};
	bottomLeft.y = float(int(m_AnimSpriteRow) * m_SrcLength);
	Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SrcLength, m_SrcLength };

	dynamic_cast<CRender*>(m_OwnerObject->GetComponent<CRender>())->SetSourceRect(src);
}

void CTankTron::SetAnimSpriteRow(int rowNr)
{
	m_AnimSpriteRow = rowNr;
	SetTexture();
}

void CTankTron::DisableWalls()
{
	m_IgnoreWalls = true;
}