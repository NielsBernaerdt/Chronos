#pragma once
#include "BObserver.h"

enum class Event
{
	ActorDied,
	ActorDamaged,
	NPCDamaged,
	NPCKilled,
	BurgerCompleted,
};

class GameState : public BObserver
{
public:
	GameState(GameObject* pPlayerPawn): m_pPlayerPawn(pPlayerPawn) {}
	virtual ~GameState() = default;
	GameState(const GameState& other) = delete;
	GameState(GameState&& other) noexcept = delete;
	GameState& operator=(const GameState& other) = delete;
	GameState& operator=(GameState&& other) noexcept = delete;

	void HandleEvent(GameObject* pGameObject, Event event) override;

private:
	GameObject* m_pPlayerPawn;

	void CheckPlayerVictory();
	void HandlePlayerDeath();
	void HandleNPCDeath(GameObject* pGameObject);
};