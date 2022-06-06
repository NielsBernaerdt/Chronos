#pragma once
#include "GameObject.h"
#include "BObserver.h"

enum class Event
{
	ActorDied,
	ActorDamaged,
	NPCKilled,
	BurgerCompleted,
};

class GameState : public BObserver
{
public:
	GameState(GameObject* playerPawn) : m_pPawn(playerPawn) {}
	void SetPawn(GameObject* pPawn) { m_pPawn = pPawn; }

	void Notify(GameObject* object, Event event) override;

private:
	void CheckPlayerVictory();

	GameObject* m_pPawn;
};