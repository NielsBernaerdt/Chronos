#pragma once
#include "GameObject.h"
#include "BObserver.h"

enum class Event
{
	ActorDied,
	NPCKilled,
	BurgerCompleted,
};

class GameState : public BObserver
{
public:
	void Notify(GameObject* object, Event event) override;

private:
	void CheckPlayerVictory();
};