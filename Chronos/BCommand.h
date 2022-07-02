#pragma once

class GameObject;

class BCommand
{
public:
	explicit BCommand() = default;
	virtual ~BCommand() = default;
	BCommand(const BCommand & other) = delete;
	BCommand(BCommand&& other) noexcept = delete;
	BCommand& operator=(const BCommand& other) = delete;
	BCommand& operator=(BCommand&& other) noexcept = delete;

	virtual void Execute(GameObject* pPawn) = 0;
};