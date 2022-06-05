#pragma once
#include <CBase.h>
#include "PlayerState.h"

class CTransform;
class PlayerState;

class CEnemyPlayer : public CBase
{
public:
	CEnemyPlayer(GameObject* gameObject);
	~CEnemyPlayer() override;
	CEnemyPlayer(const CEnemyPlayer& other) = delete;
	CEnemyPlayer(CEnemyPlayer&& other) noexcept = delete;
	CEnemyPlayer& operator=(const CEnemyPlayer& other) = delete;
	CEnemyPlayer& operator=(CEnemyPlayer&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;
	void MoveHorizontally(int moveRight);
	void ClimbLadder(int moveUp);

	void SetAnimSpriteRow(int rowNr);
	const glm::vec3& GetAccMovement() { return m_AccMovement; }

private:
	float m_MovSpeed{ 200 };
	glm::vec3 m_PrevPosition{};
	glm::vec3 m_AccMovement{};

	CTransform* m_PawnTransform = nullptr;
	CCollisionBox* m_pCollision = nullptr;

	float m_AccTime{};
	float m_AnimationDuration{ 0.125f };
	int m_SrcLength{ 16 };
	int m_AnimationIndex{ 0 };
	int m_AnimSpriteRow{ 0 };
	void SetTexture();

	//State
private:
	PlayerState* m_State = nullptr;

	void DamagePlayer();
	void BurgerCollision();
};
