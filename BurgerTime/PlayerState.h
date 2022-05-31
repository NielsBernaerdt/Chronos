#pragma once
#include "BState.h"

class GameObject;

class PlayerState : public BState
{
public:
	static class IdleState m_IdleState;
	static class WalkingState m_WalkingState;
	static class ClimbingState m_ClimbingState;

protected:
	GameObject* m_pPlayerPawn = nullptr;

public:
	PlayerState() = default;
	~PlayerState() override = default;
	PlayerState(const PlayerState& other) = delete;
	PlayerState(PlayerState&& other) noexcept = delete;
	PlayerState& operator=(const PlayerState& other) = delete;
	PlayerState& operator=(PlayerState&& other) noexcept = delete;

	void HandleInput() override {}
	void Update() override {}

	void OnEnter() override {}
	void OnExit() override {}
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

	void HandleInput() override {}
	void Update() override {}

	void OnEnter() override {}
	void OnExit() override {}
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

	void HandleInput() override {}
	void Update() override {}

	void OnEnter() override {}
	void OnExit() override {}
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

	void HandleInput() override {}
	void Update() override {}

	void OnEnter() override {}
	void OnExit() override {}
};