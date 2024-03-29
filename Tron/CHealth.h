#pragma once
#include <CBase.h>
#include <memory>

class BPublisher;

class CHealth : public CBase
{
public:
	CHealth(GameObject* pGameObject, int health = 3, std::shared_ptr<BPublisher> pPublisher = nullptr) : CBase(pGameObject), m_Health(health), m_pPublisher(pPublisher) {}
	~CHealth() override = default;
	CHealth(const CHealth & other) = delete;
	CHealth(CHealth && other) noexcept = delete;
	CHealth& operator=(const CHealth & other) = delete;
	CHealth& operator=(CHealth && other) noexcept = delete;

	void SetHealth(int hp);
	int GetHealth() const { return m_Health; }
	void Damage();

private:
	int m_Health{};

	std::shared_ptr<BPublisher> m_pPublisher;
};