#include "Commands.h"

#include "Audio.h"
#include "CTransform.h"

//----------------------------------FIRE----------------------------------
//Fire::Fire(GameObject* actor)
//	: Command(actor)
//{
//}
//Fire::~Fire()
//{
//	delete m_Actor;
//	m_Actor = nullptr;
//}
//void Fire::Execute()
//{
//	std::cout << "Fire\n";
//}
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

	m_Actor->GetTransform()->SetPosition(0, 100);

	Audio::GetInstance().PlaySound("../Data/Clock.wav", 1);
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

	m_Actor->GetTransform()->SetPosition(100, 0);
	Audio::GetInstance().PlaySound("../Data/Lock.wav", 1);
}