#include "InputCommands.h"

#include "CPeterPepper.h"
#include "AudioManager.h"
#include "CTransform.h"
#include "PlayerState.h"

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
	std::cout << "MoveRight\n";
	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>().get());
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
	std::cout << "MoveLeft\n";
	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>().get());
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
	std::cout << "ClimbUp\n";
	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>().get());
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
	std::cout << "ClimbDown\n";
	if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>().get());
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
	std::cout << "Fart\n";

	m_Actor->SetState(new WalkingState{});

	m_Actor->GetTransform()->SetPosition(100, 0);
	//AudioManager::GetInstance().PlaySound("../Data/Clock.wav", 1);
}