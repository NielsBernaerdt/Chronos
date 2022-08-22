#pragma once
#include <CBase.h>

class CPoints;
class CText;
class CHealth;

class CHUDElement : public CBase
{
public:
	CHUDElement(GameObject* gameObject, GameObject* pawnOne, GameObject* pawnTwo = nullptr);
	~CHUDElement() override = default;
	CHUDElement(const CHUDElement& other) = delete;
	CHUDElement(CHUDElement&& other) noexcept = delete;
	CHUDElement& operator=(const CHUDElement& other) = delete;
	CHUDElement& operator=(CHUDElement&& other) noexcept = delete;

	void Initialize() override;
	void Update(float deltaTime) override;

private:
	GameObject* m_PlayerOnePawn = nullptr;
	GameObject* m_PlayerTwoPawn = nullptr;
	CText* m_pTextComponent{};
	CHealth* m_pHealthComponentOne = nullptr;
	CPoints* m_pPointsComponentOne = nullptr;
	CHealth* m_pHealthComponentTwo = nullptr;
	CPoints* m_pPointsComponentTwo = nullptr;
};