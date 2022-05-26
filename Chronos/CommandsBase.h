#pragma once
#include "GameObject.h"

enum class ControllerButton
{
	DPadUp			= 0x0001,
	DPadDown		= 0x0002,
	DPadLeft		= 0x0004,
	DPadRight		= 0x0008,
	ButtonStart		= 0x0010,
	ButtonBack		= 0x0020,
	LeftThumb		= 0x0040,
	RightThumb		= 0x0080,
	LeftShoulder	= 0x0100,
	RightShoulder	= 0x0200,
	ButtonA			= 0x1000,
	ButtonB			= 0x2000,
	ButtonX			= 0x4000,
	ButtonY			= 0x8000
};

class Command
{
protected:
	GameObject* GetActor() const;
public:
	explicit Command(GameObject* actor);
	virtual ~Command() = 0;

	virtual void Execute() = 0;
protected:
	GameObject* m_Actor;
};
//
class Fire : public Command
{
public:
	Fire(GameObject* actor);
	~Fire() override;

	void Execute() override;
};