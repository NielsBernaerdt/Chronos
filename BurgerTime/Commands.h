#pragma once
#include "CommandsBase.h"

//class Fire : public Command
//{
//public:
//	Fire(GameObject* actor);
//	~Fire() override;
//
//	void Execute() override;
//};
class Duck : public Command
{
public:
	Duck(GameObject* actor);
	~Duck() override;

	void Execute() override;
};
class Jump : public Command
{
public:
	Jump(GameObject* actor);
	~Jump() override;

	void Execute() override;
};
class Fart : public Command
{
public:
	Fart(GameObject* actor);
	~Fart() override;

	void Execute() override;
};