#pragma once
#include <CBase.h>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include "CollisionGroups.h"

class CTransform;
class CCollisionBox;
class PlayerState;

class CTankTron : public CBase
{
public:
	CTankTron(GameObject* pGameObject);
	~CTankTron() override;
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
	void SetAnimSpriteRow(int rowNr);

	void DisableWalls();

private:
	float m_MovSpeed{ 200 };
	glm::vec3 m_PrevPosition{};
	glm::vec3 m_AccMovement{};
	
	glm::vec3 m_BarrelDirection{};
	float m_AccTimeShooting{ 1.f };
	float m_ShootingCooldown{ 1.f };

	CTransform* m_pPawnTransform = nullptr;
	CCollisionBox* m_pCollision = nullptr;
	CollisionGroup m_BulletCollisionGroup;

	bool m_IgnoreWalls{ false };

	//State
	int m_SrcLength{ 32 };
	int m_AnimSpriteRow{ 0 };
	void SetTexture();

private:
	PlayerState* m_pState = nullptr;
};