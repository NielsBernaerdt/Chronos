#pragma once
#include <CBase.h>

class CTankTron : public CBase
{
public:
	CTankTron(GameObject* gameObject);
	~CTankTron() override = default;
	CTankTron(const CTankTron& other) = delete;
	CTankTron(CTankTron&& other) noexcept = delete;
	CTankTron& operator=(const CTankTron& other) = delete;
	CTankTron& operator=(CTankTron&& other) noexcept = delete;
};