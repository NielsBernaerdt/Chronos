#include "CTankNPC.h"
#include <GameObject.h>
#include <CCollisionBox.h>
//Spawn bullet includes
#include <ResourceManager.h>
#include <CRender.h>
#include <CCollisionBox.h>
#include "CBullet.h"
#include "Scene.h"
#include "SceneManager.h"
#include "CollisionGroups.h"

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

void CTankNPC::Update(float deltaTime)
{
	m_AccTimeShooting += deltaTime;
	Shoot();
}

void CTankNPC::Shoot()
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
	std::unique_ptr<CBullet> bulletCBullet = std::make_unique<CBullet>(bullet.get(), m_BarrelDirection, CollisionGroup::NPC);
	bullet->AddComponent(std::move(bulletCBullet));

	SceneManager::GetInstance().GetActiveScene()->SpawnObject(bullet);
}