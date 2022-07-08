#pragma once
#include <CBase.h>
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)

class CTransform;
class CCollisionBox;

class CTankTron : public CBase
{
public:
	CTankTron(GameObject* gameObject);
	~CTankTron() override = default;
	CTankTron(const CTankTron& other) = delete;
	CTankTron(CTankTron&& other) noexcept = delete;
	CTankTron& operator=(const CTankTron& other) = delete;
	CTankTron& operator=(CTankTron&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;
	void MoveHorizontally(int moveRight);
	void MoveVertically(int moveUp);

private:
	float m_MovSpeed{ 200 };
	glm::vec3 m_PrevPosition{};
	glm::vec3 m_AccMovement{};

	CTransform* m_PawnTransform = nullptr;
	CCollisionBox* m_pCollision = nullptr;

	//State
//private:
//	PlayerState* m_State = nullptr;
};