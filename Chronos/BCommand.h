#pragma once
#include "GameObject.h"



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