#pragma once
#include "BCommand.h"

class CEnemyPlayer;
class CPeterPepper;

//----------------------------------MOVERIGHT----------------------------------
class MoveRight : public BCommand
{
public:
	MoveRight(GameObject* actor = nullptr);
	~MoveRight() override;

	void Execute() override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------MOVELEFT----------------------------------
class MoveLeft : public BCommand
{
public:
	MoveLeft(GameObject* actor = nullptr);
	~MoveLeft() override;

	void Execute() override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------CLIMBUP----------------------------------
class ClimbUp : public BCommand
{
public:
	ClimbUp(GameObject* actor = nullptr);
	~ClimbUp() override;

	void Execute() override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------CLIMBDOWN----------------------------------
class ClimbDown : public BCommand
{
public:
	ClimbDown(GameObject* actor = nullptr);
	~ClimbDown() override;

	void Execute() override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------FIRE----------------------------------
class Fire : public BCommand
{
public:
	Fire(GameObject* actor);
	~Fire() override;

	void Execute() override;
};