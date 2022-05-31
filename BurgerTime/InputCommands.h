#pragma once
#include "BCommand.h"

class Fire : public BCommand
{
public:
	Fire(GameObject* actor);
	~Fire() override;

	void Execute() override;
};
class Duck : public BCommand
{
public:
	Duck(GameObject* actor);
	~Duck() override;

	void Execute() override;
};
class Jump : public BCommand
{
public:
	Jump(GameObject* actor);
	~Jump() override;

	void Execute() override;
};
class Fart : public BCommand
{
public:
	Fart(GameObject* actor);
	~Fart() override;

	void Execute() override;
};