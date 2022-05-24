#include "ChronosPCH.h"
#include "Commands.h"

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
//----------------------------------FIRE----------------------------------
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
//----------------------------------DUCK----------------------------------
Duck::Duck(GameObject* actor)
	: Command(actor)
{
}
Duck::~Duck()
{
	delete m_Actor;
	m_Actor = nullptr;
}
void Duck::Execute()
{
	std::cout << "Duck\n";
}
//----------------------------------JUMP----------------------------------
Jump::Jump(GameObject* actor)
	: Command(actor)
{
}
Jump::~Jump()
{
	delete m_Actor;
	m_Actor = nullptr;
}
void Jump::Execute()
{
	std::cout << "Jump\n";
}
//----------------------------------FART----------------------------------
Fart::Fart(GameObject* actor)
	: Command(actor)
{
}
Fart::~Fart()
{ 
	delete m_Actor;
	m_Actor = nullptr;
}
void Fart::Execute()
{
	std::cout << "Fart\n";
}