#include "CTankNPC.h"
#include <GameObject.h>
#include <CCollisionBox.h>
//Spawn bullet includes
#include <ResourceManager.h>
#include <AudioManager.h>
#include <CRender.h>
#include <CCollisionBox.h>
#include "CBullet.h"
#include "Scene.h"
#include "SceneManager.h"
#include "CollisionGroups.h"
#include "CHealth.h"

int CTankNPC::m_NrNPCsAlive = 0;

CTankNPC::CTankNPC(GameObject* pGameObject, TankType type = TankType::BlueTank)
	: CBase(pGameObject)
	, m_Type(type)
{
	if (m_OwnerObject)
		m_pPawnTransform = m_OwnerObject->GetTransform();

	SetupTankType();

	++m_NrNPCsAlive;
}

CTankNPC::~CTankNPC()
{
	--m_NrNPCsAlive;
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
	if (m_Type == TankType::BlueTank)
	{
		m_AccTimeShooting += deltaTime;
		AutomaticShooting();
	}
	else
	{
		auto players = m_pCollision->GetOverlappingObjects(CollisionGroup::Pawn);
		if (players.empty() == false)
		{
			for (const auto& e : players)
			{
				//TP player
				e->GetTransform()->SetPosition(23, 65);
				dynamic_cast<CHealth*>(e->GetComponent<CHealth>())->Damage();
			}
		}
	}
}

void CTankNPC::AutomaticShooting()
{
	if (m_AccTimeShooting <= m_ShootingCooldown)
		return;
	m_AccTimeShooting = 0.f;

	const auto bullet = std::make_shared<GameObject>(std::string{ "bullet" });
	auto startingPos = m_OwnerObject->GetTransform()->GetPosition();
	startingPos.y += 15;
	bullet->GetTransform()->SetPosition(startingPos);
	bullet->GetTransform()->SetScale(10, 10);

	const auto bulletTexture = ResourceManager::GetInstance().LoadTexture("Tron/Bullet.png");
	std::unique_ptr<CRender> bulletCRender = std::make_unique<CRender>(bullet.get(), bulletTexture, true);
	bullet->AddComponent(std::move(bulletCRender));

	std::unique_ptr<CCollisionBox> bulletCCollision = std::make_unique<CCollisionBox>(bullet.get(), CollisionGroup::Bullet);
	bullet->AddComponent(std::move(bulletCCollision));

	std::unique_ptr<CBullet> bulletCBullet = std::make_unique<CBullet>(bullet.get(), normalize(m_BarrelDirection), CollisionGroup::NPC);
	bullet->AddComponent(std::move(bulletCBullet));

	SceneManager::GetInstance().GetActiveScene()->SpawnObject(bullet);
	AudioManager::GetInstance().PlaySound("AudioFiles/Shooting.wav", 30);
}