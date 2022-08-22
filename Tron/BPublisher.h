#pragma once
#include <vector>
#include <Memory>

class GameObject;
enum class Event;
class BObserver;

class BPublisher
{
public:
	BPublisher() = default;
	virtual ~BPublisher() = default;
	BPublisher(const BPublisher& other) = delete;
	BPublisher(BPublisher&& other) noexcept = delete;
	BPublisher& operator=(const BPublisher& other) = delete;
	BPublisher& operator=(BPublisher&& other) noexcept = delete;

	void Notify(GameObject* pGameObject, Event event) const;
	void AddObserver(std::shared_ptr<BObserver> observer);
	void RemoveObserver(std::shared_ptr<BObserver> observer);

private:
	std::vector<std::shared_ptr<BObserver>> m_pObservers;
};