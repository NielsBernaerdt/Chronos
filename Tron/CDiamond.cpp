#include "CDiamond.h"
#include <GameObject.h>
#include <CCollisionBox.h>
#include <iostream>

#include "CollisionGroups.h"
#include "Renderer.h"

CDiamond::CDiamond(GameObject* gameObject)
	:CBase(gameObject)
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
		}
	}
}

void CDiamond::TeleportPlayer(GameObject* playerPawn)
{
	int lowerBound = 40;
	int upperBound = (int)Renderer::GetInstance().GetWindowSize().x;

	//give random pos
	int x = lowerBound + (std::rand() % (upperBound - lowerBound + 1));
	int y = lowerBound + (std::rand() % (upperBound - lowerBound + 1));


	playerPawn->GetTransform()->SetPosition(x, y);
	dynamic_cast<CCollisionBox*>(playerPawn->GetComponent<CCollisionBox>())->SetRect(glm::vec2{ x, y });

	if (dynamic_cast<CCollisionBox*>(playerPawn->GetComponent<CCollisionBox>())->GetOverlappingObjects(CollisionGroup::Wall).empty() == false)
	{
		std::cout << "Hello is this working?\n";
		TeleportPlayer(playerPawn);
	}
	else
	{
		std::cout << "Okayy\n";
	}
}