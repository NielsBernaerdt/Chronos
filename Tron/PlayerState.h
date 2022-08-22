#pragma once
#include <BState.h>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

class GameObject;
class CTankTron;

class PlayerState : BState
{
public:
	PlayerState() = default;
	virtual ~PlayerState() = default;
	PlayerState(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) noexcept = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState& operator=(PlayerState&& other) noexcept = delete;

	virtual PlayerState* Update(GameObject*, CTankTron*) { return nullptr; }

protected:
	glm::vec3 m_PrevPos{};
	bool m_OnEnter = true;
};

class IdleState : public PlayerState
{
public:
	IdleState() = default;
	~IdleState() override = default;
	IdleState(const IdleState& other) = delete;
	IdleState(IdleState&& other) noexcept = delete;
	IdleState& operator=(const IdleState& other) = delete;
	IdleState& operator=(IdleState&& other) noexcept = delete;

	PlayerState* Update(GameObject* pPawn, CTankTron* pTron) override;
};

class MoveUpState : public PlayerState
{
public:
	MoveUpState() = default;
	~MoveUpState() override = default;
	MoveUpState(const MoveUpState& other) = delete;
	MoveUpState(MoveUpState&& other) noexcept = delete;
	MoveUpState& operator=(const MoveUpState& other) = delete;
	MoveUpState& operator=(MoveUpState&& other) noexcept = delete;

	PlayerState* Update(GameObject* pPawn, CTankTron* pTron) override;
};

class MoveDownState : public PlayerState
{
public:
	MoveDownState() = default;
	~MoveDownState() override = default;
	MoveDownState(const MoveDownState& other) = delete;
	MoveDownState(MoveDownState&& other) noexcept = delete;
	MoveDownState& operator=(const MoveDownState& other) = delete;
	MoveDownState& operator=(MoveDownState&& other) noexcept = delete;

	PlayerState* Update(GameObject* pPawn, CTankTron* pTron) override;
};

class MoveRightState : public PlayerState
{
public:
	MoveRightState() = default;
	~MoveRightState() override = default;
	MoveRightState(const MoveRightState& other) = delete;
	MoveRightState(MoveRightState&& other) noexcept = delete;
	MoveRightState& operator=(const MoveRightState& other) = delete;
	MoveRightState& operator=(MoveRightState&& other) noexcept = delete;

	PlayerState* Update(GameObject* pPawn, CTankTron* pTron) override;
};

class MoveLeftState : public PlayerState
{
public:
	MoveLeftState() = default;
	~MoveLeftState() override = default;
	MoveLeftState(const MoveLeftState& other) = delete;
	MoveLeftState(MoveLeftState&& other) noexcept = delete;
	MoveLeftState& operator=(const MoveLeftState& other) = delete;
	MoveLeftState& operator=(MoveLeftState&& other) noexcept = delete;

	PlayerState* Update(GameObject* pPawn, CTankTron* pTron) override;
};