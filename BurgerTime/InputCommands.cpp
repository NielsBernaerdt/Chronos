#include "InputCommands.h"

#include "CPeterPepper.h"
#include "AudioManager.h"
#include "CTransform.h"

//#define SHOW_DEBUG

//----------------------------------MOVERIGHT----------------------------------
MoveRight::MoveRight(GameObject* actor)
	: BCommand(actor)
{
	
}
MoveRight::~MoveRight()
{
}
void MoveRight::Execute()
{
#ifdef SHOW_DEBUG
	std::cout << "MoveRight\n";
	#endif

	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
	CPepper->MoveHorizontally(1);
}
//----------------------------------MOVELEFT----------------------------------
MoveLeft::MoveLeft(GameObject* actor)
	: BCommand(actor)
{
}
MoveLeft::~MoveLeft()
{
}
void MoveLeft::Execute()
{
#ifdef SHOW_DEBUG
	std::cout << "MoveLeft\n";
#endif
	
	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
	CPepper->MoveHorizontally(-1);
}
//----------------------------------CLIMBUP----------------------------------
ClimbUp::ClimbUp(GameObject* actor)
	: BCommand(actor)
{
}
ClimbUp::~ClimbUp()
{
}
void ClimbUp::Execute()
{
#ifdef SHOW_DEBUG
	std::cout << "ClimbUp\n";
#endif
	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
	CPepper->ClimbLadder(1);
}
//----------------------------------CLIMBDOWN----------------------------------
ClimbDown::ClimbDown(GameObject* actor)
	: BCommand(actor)
{
}
ClimbDown::~ClimbDown()
{
}
void ClimbDown::Execute()
{
#ifdef SHOW_DEBUG
	std::cout << "CLimbDown\n";
#endif
	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
	CPepper->ClimbLadder(-1);
}
//----------------------------------FIRE----------------------------------
Fire::Fire(GameObject* actor)
	: BCommand(actor)
{
}
Fire::~Fire()
{
}
void Fire::Execute()
{
#ifdef SHOW_DEBUG
	std::cout << "Fire\n";
#endif

	m_Actor->GetTransform()->SetPosition(100, 0);
	//AudioManager::GetInstance().PlaySound("../Data/Clock.wav", 1);
}