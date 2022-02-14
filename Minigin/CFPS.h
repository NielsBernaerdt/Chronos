#pragma once
#include "CBase.h"

class CFPS final : public CBase
{
public:
	CFPS() = default;
	virtual ~CFPS() = default;
	CFPS(const CFPS& other) = delete;
	CFPS(CFPS&& other) = delete;
	CFPS& operator=(const CFPS& other) = delete;
	CFPS& operator=(CFPS&& other) = delete;

	void Update(float deltaTime) override;
private:
};