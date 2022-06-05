#pragma once
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include <CBase.h>

class PlayerState;
class CTransform;
class CCollisionBox;

class CMrHotDog : public CBase
{
public:
	CMrHotDog(GameObject* gameObject);
	~CMrHotDog() override;
	CMrHotDog(const CMrHotDog& other) = delete;
	CMrHotDog(CMrHotDog&& other) noexcept = delete;
	CMrHotDog& operator=(const CMrHotDog& other) = delete;
	CMrHotDog& operator=(CMrHotDog&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;

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

	void DamagePlayer();
	void BurgerCollision();
};