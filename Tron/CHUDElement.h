#pragma once
#include <CBase.h>

class CPoints;
class CText;
class CHealth;

class CHUDElement : public CBase
{
public:
	CHUDElement(GameObject* gameObject, GameObject* objectToFollow);
	~CHUDElement() override = default;
	CHUDElement(const CHUDElement& other) = delete;
	CHUDElement(CHUDElement&& other) noexcept = delete;
	CHUDElement& operator=(const CHUDElement& other) = delete;
	CHUDElement& operator=(CHUDElement&& other) noexcept = delete;

	void Initialize() override;
	void Update(float deltaTime) override;

private:
	GameObject* m_pObjectToFollow = nullptr;
	CText* m_pTextComponent{};
	CHealth* m_pHealthComponent = nullptr;
	CPoints* m_pPointsComponent = nullptr;
};