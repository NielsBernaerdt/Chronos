#include "CDiamond.h"
#include <GameObject.h>
#include <CCollisionBox.h>
#include <iostream>
#include <AudioManager.h>
#include "CollisionGroups.h"
#include "Renderer.h"

CDiamond::CDiamond(GameObject* pGameObject)
	:CBase(pGameObject)
{
}

void CDiamond::Initialize()
{
	m_pCollision = dynamic_cast<CCollisionBox*>(m_OwnerObject->GetComponent<CCollisionBox>());
}

void CDiamond::Update(float)
{
	auto collidingPlayers = m_pCollision->GetOverlappingObjects(CollisionGroup::Pawn);
	if (collidingPlayers.empty() == false)
	{
		for (const auto& p : collidingPlayers)
		{
			TeleportPlayer(p);
			AudioManager::GetInstance().PlaySound("AudioFiles/TeleportSound.wav", 30);
		}
	}
}

void CDiamond::TeleportPlayer(GameObject* pPlayerPawn)
{
	int lowerBound = 40;
	int upperBound = (int)Renderer::GetInstance().GetWindowSize().x;

	//give random pos
	int x = lowerBound + (std::rand() % (upperBound - lowerBound + 1));
	int y = lowerBound + (std::rand() % (upperBound - lowerBound + 1));


	pPlayerPawn->GetTransform()->SetPosition(x, y);
	dynamic_cast<CCollisionBox*>(pPlayerPawn->GetComponent<CCollisionBox>())->SetRect(glm::vec2{ x, y });

	if (dynamic_cast<CCollisionBox*>(pPlayerPawn->GetComponent<CCollisionBox>())->GetOverlappingObjects(CollisionGroup::Wall).empty() == false)
	{
		TeleportPlayer(pPlayerPawn);
	}
}