#pragma once
#include "BState.h"

#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

class CCollisionBox;
class CPeterPepper;
class GameObject;

class PlayerState : BState
{
public:
	PlayerState() = default;
	virtual ~PlayerState() = default;
	PlayerState(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) noexcept = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState& operator=(PlayerState&& other) noexcept = delete;

	virtual PlayerState* Update(GameObject*, CPeterPepper*) { return nullptr; }
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

	PlayerState* Update(GameObject* pPawn, CPeterPepper* pPeter) override;
private:
	glm::vec3 m_PrevPos{};
	bool m_DoOnce = true;
};

class WalkingState : public PlayerState
{
public:
	WalkingState() = default;
	~WalkingState() override = default;
	WalkingState(const WalkingState& other) = delete;
	WalkingState(WalkingState&& other) noexcept = delete;
	WalkingState& operator=(const WalkingState& other) = delete;
	WalkingState& operator=(WalkingState&& other) noexcept = delete;

	PlayerState* Update(GameObject* pPawn, CPeterPepper* pPeter) override;

private:
	glm::vec3 m_PrevPos{};
	bool m_DoOnce = true;

	CCollisionBox* m_pCollision = nullptr;
};

class ClimbingState : public PlayerState
{
public:
	ClimbingState() = default;
	~ClimbingState() override = default;
	ClimbingState(const ClimbingState& other) = delete;
	ClimbingState(ClimbingState&& other) noexcept = delete;
	ClimbingState& operator=(const ClimbingState& other) = delete;
	ClimbingState& operator=(ClimbingState&& other) noexcept = delete;

	PlayerState* Update(GameObject* pPawn, CPeterPepper* pPeter) override;

private:
	bool m_DoOnce = true;

	CCollisionBox* m_pCollision = nullptr;
};