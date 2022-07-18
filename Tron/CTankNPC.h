#pragma once
#include <CBase.h>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

class CTransform;
class CCollisionBox;

enum class TankType
{
	BlueTank,
	Recognizer
};

class CTankNPC : public CBase
{
public:
	CTankNPC(GameObject* gameObject, TankType type);
	~CTankNPC() override = default;
	CTankNPC(const CTankNPC& other) = delete;
	CTankNPC(CTankNPC&& other) noexcept = delete;
	CTankNPC& operator=(const CTankNPC& other) = delete;
	CTankNPC& operator=(CTankNPC&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;

private:
	TankType m_Type{};
	float m_MovSpeed{ 200 };
	int m_PointsWorth{ 100 };
	glm::vec3 m_PrevPosition{};
	glm::vec3 m_AccMovement{};

	glm::vec3 m_BarrelDirection{};
	float m_AccTimeShooting{ 1.f };
	float m_ShootingCooldown{ 1.f };

	CTransform* m_PawnTransform = nullptr;
	CCollisionBox* m_pCollision = nullptr;

	void SetupTankType();
};