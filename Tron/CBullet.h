#pragma once
#include <CBase.h>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

class CTransform;
class CCollisionBox;

class CBullet : public CBase
{
public:
	CBullet(GameObject* gameObject, glm::vec3 velocity = glm::vec3{});
	~CBullet() override = default;
	CBullet(const CBullet& other) = delete;
	CBullet(CBullet&& other) noexcept = delete;
	CBullet& operator=(const CBullet& other) = delete;
	CBullet& operator=(CBullet&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;

private:
	int m_NrBounces{};
	const int m_MaxNrBounces{ 5 };
	glm::vec3 m_PrevPosition{};
	glm::vec3 m_Velocity{};
	float m_BulletSpeed{ 3 };

	CTransform* m_PawnTransform = nullptr;
	CCollisionBox* m_pCollision = nullptr;

	void BounceBullet();
};