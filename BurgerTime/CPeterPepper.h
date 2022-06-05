#pragma once
#include <CBase.h>
#include "PlayerState.h"

class CTransform;

class CPeterPepper : public CBase
{
public:
	CPeterPepper(GameObject* gameObject);
	~CPeterPepper() override;
	CPeterPepper(const CPeterPepper& other) = delete;
	CPeterPepper(CPeterPepper&& other) noexcept = delete;
	CPeterPepper& operator=(const CPeterPepper& other) = delete;
	CPeterPepper& operator=(CPeterPepper&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;
	void MoveHorizontally(int moveRight);
	void ClimbLadder(int moveUp);

	void SetAnimSpriteRow(int rowNr);
	const glm::vec3& GetAccMovement() { return m_AccMovement; }

private:
	float m_MovSpeed{200};
	glm::vec3 m_PrevPosition{};
	glm::vec3 m_AccMovement{};

	CTransform* m_PawnTransform = nullptr;
	CCollisionBox* m_pCollision = nullptr;

	float m_AccTime{};
	float m_AnimationDuration{ 0.125f };
	int m_SrcLength{ 16 };
	int m_AnimationIndex{ 0 };
	int m_AnimSpriteRow{ 0 };
	int m_WasWalkingUpwards{ -1 };
	void SetTexture();

	//State
private:
	PlayerState* m_State = nullptr;
};
