#pragma once
class GameObject;
enum class Event;

class BObserver
{
public:
	BObserver() = default;
	virtual ~BObserver() = default;
	BObserver(const BObserver& other) = delete;
	BObserver(BObserver&& other) noexcept = delete;
	BObserver& operator=(const BObserver& other) = delete;
	BObserver& operator=(BObserver&& other) noexcept = delete;

	virtual void HandleEvent(GameObject* object, Event event) = 0;
};