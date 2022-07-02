#include "InputCommands.h"
#include "CEnemyPlayer.h"
#include "CPeterPepper.h"
//
#include "GameObject.h"
#include "CRender.h"
#include <memory>
#include "CCollisionBox.h"
#include "CollisionGroups.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
//#define SHOW_DEBUG

//----------------------------------MOVERIGHT----------------------------------
MoveRight::MoveRight()
	: BCommand()
{
}
MoveRight::~MoveRight()
{
}
void MoveRight::Execute(GameObject* actor)
{
#ifdef SHOW_DEBUG
	std::cout << "MoveRight\n";
	#endif
	if (CPepper == nullptr && CHotDog == nullptr)
	{
		if (!actor) return;
		if (actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if (usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(actor->GetComponent<CPeterPepper>());
		CPepper->MoveHorizontally(1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(actor->GetComponent<CEnemyPlayer>());
		CHotDog->MoveHorizontally(1);
	}
}
//----------------------------------MOVELEFT----------------------------------
MoveLeft::MoveLeft()
	: BCommand()
{
}
MoveLeft::~MoveLeft()
{
}
void MoveLeft::Execute(GameObject* actor)
{
#ifdef SHOW_DEBUG
	std::cout << "MoveLeft\n";
#endif
	if (CPepper == nullptr && CHotDog == nullptr)
	{
		if (!actor) return;
		if (actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if (usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(actor->GetComponent<CPeterPepper>());
		CPepper->MoveHorizontally(-1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(actor->GetComponent<CEnemyPlayer>());
		CHotDog->MoveHorizontally(-1);
	}
}
//----------------------------------CLIMBUP----------------------------------
ClimbUp::ClimbUp()
	: BCommand()
{
}
ClimbUp::~ClimbUp()
{
}
void ClimbUp::Execute(GameObject* actor)
{
#ifdef SHOW_DEBUG
	std::cout << "ClimbUp\n";
#endif
	if (CPepper == nullptr && CHotDog == nullptr)
	{
		if (!actor) return;
		if (actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if(usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(actor->GetComponent<CPeterPepper>());
		CPepper->ClimbLadder(1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(actor->GetComponent<CEnemyPlayer>());
		CHotDog->ClimbLadder(1);
	}
}
//----------------------------------CLIMBDOWN----------------------------------
ClimbDown::ClimbDown()
	: BCommand()
{
}
ClimbDown::~ClimbDown()
{
}
void ClimbDown::Execute(GameObject* actor)
{
#ifdef SHOW_DEBUG
	std::cout << "CLimbDown\n";
#endif
	if(CPepper == nullptr && CHotDog == nullptr)
	{
		if (!actor) return;
		if (actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if (usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(actor->GetComponent<CPeterPepper>());
		CPepper->ClimbLadder(-1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(actor->GetComponent<CEnemyPlayer>());
		CHotDog->ClimbLadder(-1);
	}
}
//----------------------------------FIRE----------------------------------
Fire::Fire()
	: BCommand()
{
}
Fire::~Fire()
{
}
void Fire::Execute(GameObject* actor)
{
#ifdef SHOW_DEBUG
	std::cout << "Fire\n";
#endif

	actor->GetTransform()->SetPosition(100, 0);
}