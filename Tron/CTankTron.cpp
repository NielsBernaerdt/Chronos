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
//CTankTron::~CTankTron()
//{
//	delete m_State;
//	m_State = nullptr;
//}

void CTankTron::Initialize()
{
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
	//m_State = new IdleState{};
}
void CTankTron::Update(float deltaTime)
{
	//m_AccTime += deltaTime;
	////LET BARREL ROTATE
	//auto child = m_OwnerObject->GetChildren()[0];
	//auto baseComp = child->GetComponent<CRender>();
	//auto renderComp = dynamic_cast<CRender*>(baseComp);
	//std::cout << "Float time: " << m_AccTime << std::endl;
	//std::cout << "Int time: " << (int)m_AccTime << std::endl;

	//renderComp->RotateTexture(15 * int(m_AccTime));

	m_AccTimeShooting += deltaTime;
	//LET BARREL ROTATE
	auto child = m_OwnerObject->GetChildren()[0];
	auto baseComp = child->GetComponent<CRender>();
	auto renderComp = dynamic_cast<CRender*>(baseComp);

	//MATH HERE//
	float angle{};
	glm::vec2 mousePos = InputManager::GetMousePos();

	mousePos.x -= m_OwnerObject->GetTransform()->GetPosition().x;
	mousePos.y -= m_OwnerObject->GetTransform()->GetPosition().y;

	//
	m_BarrelDirection = { mousePos.x, mousePos.y, 0 };
	//

	angle = atanf(mousePos.y/ mousePos.x);
	angle = float(angle * 180 / 3.14159265358979323846264338327950288);
	//std::cout << "Float angle: " << angle << std::endl;
	//std::cout << "Int time: " << int(angle) << std::endl;
	//
	renderComp->RotateTexture(int(angle));


	//STATES//
	//PlayerState* state = m_State->Update(this->m_OwnerObject, this);
	//if (state != nullptr)
	//{
	//	delete m_State;
	//	m_State = state;
	//}

	//MOVEMENT//
	if (m_pCollision->GetOverlappingObjects(CollisionGroup::Wall).empty() == false)
	{
		m_AccMovement = { 0, 0, 0 };
		m_PawnTransform->SetPosition(m_PrevPosition);
	}
	m_PrevPosition = m_PawnTransform->GetPosition();
	m_PawnTransform->SetPosition(m_PawnTransform->GetPosition() + (m_AccMovement * deltaTime));
	m_AccMovement = { 0,0,0 };
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

	std::unique_ptr<CCollisionBox> bulletCCollision = std::make_unique<CCollisionBox>(bullet.get(), CollisionGroup::Wall);
	bullet->AddComponent(std::move(bulletCCollision));

	//todo why does this not work correctly
	glm::normalize(m_BarrelDirection);
	std::unique_ptr<CBullet> bulletCBullet = std::make_unique<CBullet>(bullet.get(), m_BarrelDirection);
	bullet->AddComponent(std::move(bulletCBullet));

	int currentScene = SceneManager::GetInstance().GetActiveScene();
	SceneManager::GetInstance().GetScene(currentScene)->Add(bullet);
}