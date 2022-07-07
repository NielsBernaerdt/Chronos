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