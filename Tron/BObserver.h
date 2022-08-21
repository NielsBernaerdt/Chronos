#pragma once

class GameObject;

enum class Event
{
	ActorDied,
	ActorDamaged,
	NPCKilled,
	BurgerCompleted,
};

class BObserver
{
public:
	BObserver() = default;
	~BObserver() = default;
	BObserver(const BObserver& other) = delete;
	BObserver(BObserver&& other) noexcept = delete;
	BObserver& operator=(const BObserver& other) = delete;
	BObserver& operator=(BObserver&& other) noexcept = delete;

	void Notify(GameObject* object, Event event);

private:
	void CheckPlayerVictory();
};