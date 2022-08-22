#pragma once
#include <CBase.h>

class CCollisionBox;

class CDiamond : public CBase
{
public:
	CDiamond(GameObject* gameObject);
	~CDiamond() override = default;
	CDiamond(const CDiamond& other) = delete;
	CDiamond(CDiamond&& other) noexcept = delete;
	CDiamond& operator=(const CDiamond& other) = delete;
	CDiamond& operator=(CDiamond&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;

private:
	CCollisionBox* m_pCollision = nullptr;

	void TeleportPlayer( GameObject* pPlayerPawn);
};
