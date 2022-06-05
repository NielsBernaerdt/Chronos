#include "InputCommands.h"
#include "CEnemyPlayer.h"
#include "CPeterPepper.h"
//
#include "CRender.h"
#include <memory>
#include "CCollisionBox.h"
#include "CollisionGroups.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "Scene.h"
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
	if (CPepper == nullptr && CHotDog == nullptr)
	{
		if (m_Actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (m_Actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if (usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
		CPepper->MoveHorizontally(1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(m_Actor->GetComponent<CEnemyPlayer>());
		CHotDog->MoveHorizontally(1);
	}
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
	//ATTEMPT AT SPAWNING
	//const auto ladderTexture = ResourceManager::GetInstance().LoadEmptyTexture();

	//const auto ladder0 = std::make_shared<GameObject>(std::string{ "Ladder" });
	//ladder0->GetTransform()->SetPosition(300, 400);
	//ladder0->GetTransform()->SetScale(30, 200);
	//std::unique_ptr<CCollisionBox> ladderCCollision0 = std::make_unique<CCollisionBox>(ladder0.get(), CollisionGroup::Ladder);
	//ladder0->AddComponent(std::move(ladderCCollision0));
	//std::unique_ptr<CRender> ladderCRender0 = std::make_unique<CRender>(ladder0.get(), ladderTexture, true);
	//ladder0->AddComponent(std::move(ladderCRender0));

	//SceneManager::GetInstance().GetScene(0)->Add(ladder0);

	//ladder0->Initialize();









#ifdef SHOW_DEBUG
	std::cout << "MoveLeft\n";
#endif
	if (CPepper == nullptr && CHotDog == nullptr)
	{
		if (m_Actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (m_Actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if (usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
		CPepper->MoveHorizontally(-1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(m_Actor->GetComponent<CEnemyPlayer>());
		CHotDog->MoveHorizontally(-1);
	}
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
	if (CPepper == nullptr && CHotDog == nullptr)
	{
		if (m_Actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (m_Actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if(usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
		CPepper->ClimbLadder(1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(m_Actor->GetComponent<CEnemyPlayer>());
		CHotDog->ClimbLadder(1);
	}
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
	if(CPepper == nullptr && CHotDog == nullptr)
	{
		if (m_Actor->GetComponent<CPeterPepper>()) usePepper = true;
		else if (m_Actor->GetComponent<CEnemyPlayer>()) usePepper = false;
	}
	if (usePepper == true)
	{
		if (CPepper == nullptr)	CPepper = dynamic_cast<CPeterPepper*>(m_Actor->GetComponent<CPeterPepper>());
		CPepper->ClimbLadder(-1);
	}
	else
	{
		if (CHotDog == nullptr)	CHotDog = dynamic_cast<CEnemyPlayer*>(m_Actor->GetComponent<CEnemyPlayer>());
		CHotDog->ClimbLadder(-1);
	}
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
}