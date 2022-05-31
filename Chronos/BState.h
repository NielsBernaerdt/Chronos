#pragma once

class BState
{
public:
	BState() = default;
	virtual ~BState() = default;
	BState(const BState& other) = delete;
	BState(BState&& other) noexcept = delete;
	BState& operator=(const BState& other) = delete;
	BState& operator=(BState&& other) noexcept = delete;

	virtual void HandleInput() {}
	virtual void Update() {}

	virtual void OnEnter() {}
	virtual void OnExit() {}
};