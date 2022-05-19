#pragma once
#include "CBase.h"

class CText;
class CRender;

class CFPS final : public CBase
{
public:
	CFPS(GameObject* gameObject);
	~CFPS() override = default;
	CFPS(const CFPS& other) = delete;
	CFPS(CFPS&& other) = delete;
	CFPS& operator=(const CFPS& other) = delete;
	CFPS& operator=(CFPS&& other) = delete;

	void Initialize() override;
	void Update(float deltaTime) override;
	
private:
	std::shared_ptr<CText> m_pTextComponent{};

	bool m_FirstUpdate = true;
	int m_PreviousFPS{};
	float m_Interval = 1.0f;
	float m_AccTime = 1.1f;
};