#pragma once
#include <CBase.h>

class CCollisionBox;

class CPlate : public CBase
{
public:
	CPlate(GameObject* gameObject) : CBase(gameObject) {}
	~CPlate() override = default;
	CPlate(const CPlate& other) = delete;
	CPlate(CPlate&& other) noexcept = delete;
	CPlate& operator=(const CPlate& other) = delete;
	CPlate& operator=(CPlate&& other) noexcept = delete;

	void Initialize() override {}
	void Update(float) override{}
};