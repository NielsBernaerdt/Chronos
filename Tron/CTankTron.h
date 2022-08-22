#pragma once
#include <CBase.h>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include "CollisionGroups.h"

class CTransform;
class CCollisionBox;

class CTankTron : public CBase
{
public:
	CTankTron(GameObject* gameObject);
	~CTankTron() override = default;
	CTankTron(const CTankTron& other) = delete;
	CTankTron(CTankTron&& other) noexcept = delete;
	CTankTron& operator=(const CTankTron& other) = delete;
	CTankTron& operator=(CTankTron&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;
	void MoveHorizontally(int moveRight);
	void MoveVertically(int moveUp);

	void Shoot();
	void SetBarrelDirection(glm::vec3  barrelDirection) { m_BarrelDirection = barrelDirection; }

private:
	float m_MovSpeed{ 200 };
	glm::vec3 m_PrevPosition{};
	glm::vec3 m_AccMovement{};
	
	glm::vec3 m_BarrelDirection{};
	float m_AccTimeShooting{ 1.f };
	float m_ShootingCooldown{ 1.f };

	CTransform* m_PawnTransform = nullptr;
	CCollisionBox* m_pCollision = nullptr;
	CollisionGroup m_BulletCollisionGroup;

	//State
//private:
//	PlayerState* m_State = nullptr;
};