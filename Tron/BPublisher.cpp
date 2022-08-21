#include "ChronosPCH.h"
#include "BPublisher.h"
#include "GameObject.h"
#include "BObserver.h"
#include <algorithm>
#include <iterator>


void BPublisher::AddObserver(std::shared_ptr<BObserver> observer)
{
	m_pObservers.push_back(observer);
}
void BPublisher::RemoveObserver(std::shared_ptr<BObserver>)
{
	//const auto it = std::ranges::find(m_pObservers, observer);

	//if (it == m_pObservers.end())
	//{
	//	std::cout << "GameObject::RemoveObserver - Observer to remove is not attached to this GameObject!" << std::endl;
	//	return;
	//}

	//m_pObservers.erase(it);
}
void BPublisher::Notify(GameObject* gameObject, Event event) const
{
	for (const auto& observer : m_pObservers)
	{
		observer->Notify(gameObject, event);
	}
}