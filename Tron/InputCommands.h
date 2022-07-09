#pragma once
#include <BCommand.h>

class CTankTron;

//----------------------------------MOVERIGHT----------------------------------
class MoveHorizontal : public BCommand
{
public:
	MoveHorizontal(bool moveRight);
	~MoveHorizontal() override;

	void Execute(GameObject* actor) override;

private:
	int m_DirectionValue;
	bool m_IsPlayerPawn;
	CTankTron* m_CTron = nullptr;
};
//----------------------------------MOVEUP----------------------------------
class MoveVertical : public BCommand
{
public:
	MoveVertical(bool moveUp);
	~MoveVertical() override;

	void Execute(GameObject* actor) override;

private:
	int m_DirectionValue;
	bool m_IsPlayerPawn;
	CTankTron* m_CTron = nullptr;
};
//----------------------------------SHOOT----------------------------------
class Shoot : public BCommand
{
public:
	Shoot();
	~Shoot() override;

	void Execute(GameObject* actor) override;

private:
	bool m_IsPlayerPawn;
	CTankTron* m_CTron = nullptr;
};