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

class BCommand
{
protected:
	GameObject* GetActor() const { return m_Actor; }

public:
	explicit BCommand(GameObject* actor) : m_Actor(actor) {}
	virtual ~BCommand() = default;
	BCommand(const BCommand & other) = delete;
	BCommand(BCommand&& other) noexcept = delete;
	BCommand& operator=(const BCommand& other) = delete;
	BCommand& operator=(BCommand&& other) noexcept = delete;

	void SetOwner(GameObject* pPawn) { m_Actor = pPawn; }
	virtual void Execute() = 0;

protected:
	GameObject* m_Actor;
};