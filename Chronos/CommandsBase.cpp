#include "ChronosPCH.h"
#include "CommandsBase.h"

Command::Command(GameObject* actor)
	: m_Actor(actor)
{
}
Command::~Command()
{
}
GameObject* Command::GetActor() const
{
	return m_Actor;
}
void Command::SetOwner(GameObject* pPawn)
{
	m_Actor = pPawn;
}

Fire::Fire(GameObject* actor)
	: Command(actor)
{
}
Fire::~Fire()
{
	delete m_Actor;
	m_Actor = nullptr;
}
void Fire::Execute()
{
	std::cout << "Fire\n";
}