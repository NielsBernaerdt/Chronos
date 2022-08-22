#include "ChronosPCH.h"
#include <algorithm>
#include <iterator>
#include <GameObject.h>
#include "BPublisher.h"
#include "BObserver.h"

void BPublisher::AddObserver(std::shared_ptr<BObserver> pObserver)
{
	m_pObservers.push_back(pObserver);
}
void BPublisher::RemoveObserver(std::shared_ptr<BObserver> pObserver)
{
	const auto it = std::find(m_pObservers.begin(), m_pObservers.end(), pObserver);

	if (it == m_pObservers.end())
	{
		std::cout << "GameObject::RemoveObserver - Observer to remove is not attached to this GameObject!" << std::endl;
		return;
	}

	m_pObservers.erase(it);
}
void BPublisher::Notify(GameObject* pGameObject, Event event) const
{
	for (const auto& observer : m_pObservers)
	{
		observer->HandleEvent(pGameObject, event);
	}
}