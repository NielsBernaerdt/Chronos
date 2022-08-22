#include "CTankTron.h"

#include <GameObject.h>
#include <CCollisionBox.h>
#include <CRender.h>
#include <iostream>
#include "CollisionGroups.h"
#include "InputManager.h"
//SPAWN BULLET
#include "ResourceManager.h"
#include "CBullet.h"
#include "Scene.h"
#include "SceneManager.h"

CTankTron::CTankTron(GameObject* gameObject)
	: CBase(gameObject)
{
	if (m_OwnerObject)
		m_PawnTransform = m_OwnerObject->GetTransform();
}

void CTankTron::Initialize()
{
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
	m_BulletCollisionGroup = m_pCollision->GetCollisionGroup();

	//m_State = new IdleState{};
}
void CTankTron::Update(float deltaTime)
{
	m_AccTimeShooting += deltaTime;


	//STATES//
	//PlayerState* state = m_State->Update(this->m_OwnerObject, this);
	//if (state != nullptr)
	//{
	//	delete m_State;
	//	m_State = state;
	//}

	//MOVEMENT// 
//CHECK IF STUCK//
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall).empty() == false)
	{
		m_PawnTransform->SetPosition(m_PrevPosition);
	}
	m_PrevPosition = m_PawnTransform->GetPosition();
//IF NOT: CHANGE POS//
	const auto newPosY = m_PawnTransform->GetPosition() + glm::vec3{ 0, m_AccMovement.y, 0 } *deltaTime;
	const Rect newRectY{ (int)newPosY.x, (int)newPosY.y, (int)m_PawnTransform->GetScale().x, (int)m_PawnTransform->GetScale().y };
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall, newRectY).empty())
	{
		m_PrevPosition = m_PawnTransform->GetPosition();
		m_PawnTransform->SetPosition(newPosY);
	}
	const auto newPosX = m_PawnTransform->GetPosition() + glm::vec3{ m_AccMovement.x, 0, 0 } *deltaTime;
	const Rect newRectX{ (int)newPosX.x, (int)newPosX.y, (int)m_PawnTransform->GetScale().x, (int)m_PawnTransform->GetScale().y };
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall, newRectX).empty())
	{
		m_PrevPosition = m_PawnTransform->GetPosition();
		m_PawnTransform->SetPosition(newPosX);
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

	const auto bullet = std::make_shared<GameObject>(std::string{ "bullet" });
	auto startingPos = m_OwnerObject->GetTransform()->GetPosition();
	bullet->GetTransform()->SetPosition(startingPos);
	bullet->GetTransform()->SetScale(20, 20);

	const auto bulletTexture = ResourceManager::GetInstance().LoadEmptyTexture();
	std::unique_ptr<CRender> bulletCRender = std::make_unique<CRender>(bullet.get(), bulletTexture, true);
	bullet->AddComponent(std::move(bulletCRender));

	std::unique_ptr<CCollisionBox> bulletCCollision = std::make_unique<CCollisionBox>(bullet.get(), CollisionGroup::Bullet);
	bullet->AddComponent(std::move(bulletCCollision));

	//todo why does this not work correctly
	glm::normalize(m_BarrelDirection);
	std::unique_ptr<CBullet> bulletCBullet = std::make_unique<CBullet>(bullet.get(), m_BarrelDirection, m_BulletCollisionGroup);
	bullet->AddComponent(std::move(bulletCBullet));

	SceneManager::GetInstance().GetActiveScene()->SpawnObject(bullet);
}