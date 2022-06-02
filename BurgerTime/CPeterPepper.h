#pragma once
#include <CBase.h>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

class CTransform;

class CPeterPepper : public CBase
{
public:
	CPeterPepper(GameObject* gameObject);
	~CPeterPepper() override = default;
	CPeterPepper(const CPeterPepper& other) = delete;
	CPeterPepper(CPeterPepper&& other) noexcept = delete;
	CPeterPepper& operator=(const CPeterPepper& other) = delete;
	CPeterPepper& operator=(CPeterPepper&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;
	void MoveHorizontally(int moveRight);
	void ClimbLadder(int moveUp);

private:
	float m_MovSpeed{200};
	glm::vec3 m_AccMovement;

	CTransform* m_PawnTransform;

	int m_SrcLength{ 16 };
	int m_AnimationIndex{ 0 };
	int m_CurrentState{ 0 };
	void SetTexture();
};
