#pragma once
#include "BCommand.h"

class CEnemyPlayer;
class CPeterPepper;

//----------------------------------MOVERIGHT----------------------------------
class MoveRight : public BCommand
{
public:
	MoveRight();
	~MoveRight() override;

	void Execute(GameObject* actor) override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------MOVELEFT----------------------------------
class MoveLeft : public BCommand
{
public:
	MoveLeft();
	~MoveLeft() override;

	void Execute(GameObject* actor) override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------CLIMBUP----------------------------------
class ClimbUp : public BCommand
{
public:
	ClimbUp();
	~ClimbUp() override;

	void Execute(GameObject* actor) override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------CLIMBDOWN----------------------------------
class ClimbDown : public BCommand
{
public:
	ClimbDown();
	~ClimbDown() override;

	void Execute(GameObject* actor) override;

private:
	bool usePepper = true;
	CPeterPepper* CPepper = nullptr;
	CEnemyPlayer* CHotDog = nullptr;
};
//----------------------------------FIRE----------------------------------
class Fire : public BCommand
{
public:
	Fire();
	~Fire() override;

	void Execute(GameObject* actor) override;
};