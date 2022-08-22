#include "PlayerState.h"
#include <GameObject.h>
#include "CTankTron.h"

PlayerState* IdleState::Update(GameObject* pPawn, CTankTron*)
{
	if (m_OnEnter)
	{
		m_OnEnter = false;
		m_PrevPos = pPawn->GetTransform()->GetPosition();

		return nullptr;
	}

	glm::vec2 accMovement = m_PrevPos - pPawn->GetTransform()->GetPosition();

	if (accMovement == glm::vec2{0, 0})
		return nullptr;
	if (accMovement.x < -0.1f)
		return new MoveRightState;
	if (accMovement.x > 0.1f)
		return new MoveLeftState;
	if (accMovement.y < -0.1f)
		return new MoveDownState;
	if (accMovement.y > 0.1f)
		return new MoveUpState;

	m_PrevPos = pPawn->GetTransform()->GetPosition();
	return nullptr;
}

PlayerState* MoveUpState::Update(GameObject* pPawn, CTankTron* pTron)
{
	if (m_OnEnter)
	{
		m_OnEnter = false;
		m_PrevPos = pPawn->GetTransform()->GetPosition();

		pTron->SetAnimSpriteRow(0);

		return nullptr;
	}

	glm::vec2 accMovement = m_PrevPos - pPawn->GetTransform()->GetPosition();

	if (accMovement == glm::vec2{ 0, 0 })
		return new IdleState{};
	if (accMovement.x < -0.1f)
		return new MoveRightState;
	if (accMovement.x > 0.1f)
		return new MoveLeftState;
	if (accMovement.y < -0.1f)
		return new MoveDownState;

	m_PrevPos = pPawn->GetTransform()->GetPosition();
	return nullptr;
}

PlayerState* MoveDownState::Update(GameObject* pPawn, CTankTron* pTron)
{
	if (m_OnEnter)
	{
		m_OnEnter = false;
		m_PrevPos = pPawn->GetTransform()->GetPosition();

		pTron->SetAnimSpriteRow(2);

		return nullptr;
	}

	glm::vec2 accMovement = m_PrevPos - pPawn->GetTransform()->GetPosition();

	if (accMovement == glm::vec2{ 0, 0 })
		return new IdleState{};
	if (accMovement.x < -0.1f)
		return new MoveRightState;
	if (accMovement.x > 0.1f)
		return new MoveLeftState;
	if (accMovement.y > 0.1f)
		return new MoveUpState;

	m_PrevPos = pPawn->GetTransform()->GetPosition();
	return nullptr;
}

PlayerState* MoveRightState::Update(GameObject* pPawn, CTankTron* pTron)
{
	if (m_OnEnter)
	{
		m_OnEnter = false;
		m_PrevPos = pPawn->GetTransform()->GetPosition();

		pTron->SetAnimSpriteRow(1);

		return nullptr;
	}

	glm::vec2 accMovement = m_PrevPos - pPawn->GetTransform()->GetPosition();

	if (accMovement == glm::vec2{ 0, 0 })
		return new IdleState{};
	if (accMovement.x > 0.1f)
		return new MoveLeftState;
	if (accMovement.y < -0.1f)
		return new MoveDownState;
	if (accMovement.y > 0.1f)
		return new MoveUpState;

	m_PrevPos = pPawn->GetTransform()->GetPosition();
	return nullptr;
}

PlayerState* MoveLeftState::Update(GameObject* pPawn, CTankTron* pTron)
{
	if (m_OnEnter)
	{
		m_OnEnter = false;
		m_PrevPos = pPawn->GetTransform()->GetPosition();

		pTron->SetAnimSpriteRow(3);

		return nullptr;
	}

	glm::vec2 accMovement = m_PrevPos - pPawn->GetTransform()->GetPosition();

	if (accMovement == glm::vec2{ 0, 0 })
		return new IdleState{};
	if (accMovement.x < -0.1f)
		return new MoveRightState;
	if (accMovement.y < -0.1f)
		return new MoveDownState;
	if (accMovement.y > 0.1f)
		return new MoveUpState;

	m_PrevPos = pPawn->GetTransform()->GetPosition();
	return nullptr;
}