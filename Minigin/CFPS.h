#pragma once
#include "CBase.h"

class CText;
class CRender;

class CFPS final : public CBase
{
public:
	CFPS(GameObject* gameObject);
	virtual ~CFPS() = default;
	CFPS(const CFPS& other) = delete;
	CFPS(CFPS&& other) = delete;
	CFPS& operator=(const CFPS& other) = delete;
	CFPS& operator=(CFPS&& other) = delete;

	void Initialize() override;
	void Update(float deltaTime) override;
	
private:
	std::shared_ptr<CText> m_pTextComponent;
	std::shared_ptr<CRender> m_pRenderComponent;
	int m_PreviousFPS = 0;
	float m_Interval = 1.0f;
	float m_AccTime;
};