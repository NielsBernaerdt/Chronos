#pragma once
#include <CBase.h>

class CPlate : public CBase
{
public:
	CPlate(GameObject* gameObject, bool final = false) : CBase(gameObject), m_IsFinal(final) {}
	~CPlate() override = default;
	CPlate(const CPlate& other) = delete;
	CPlate(CPlate&& other) noexcept = delete;
	CPlate& operator=(const CPlate& other) = delete;
	CPlate& operator=(CPlate&& other) noexcept = delete;

	void Initialize() override {}
	void Update(float) override{}

	bool IsFinalPlate() { return m_IsFinal; }

private:
	bool m_IsFinal{ false };
};