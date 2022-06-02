#pragma once
#include "CBase.h"
#include "Rect.h"

class CCollisionBox : public CBase
{
public:
	CCollisionBox(GameObject* gameObject, Rect rect, bool enableOverlap = false);
	~CCollisionBox() override = default;
	CCollisionBox(const CCollisionBox& other) = delete;
	CCollisionBox(CCollisionBox&& other) noexcept = delete;
	CCollisionBox& operator=(const CCollisionBox& other) = delete;
	CCollisionBox& operator=(CCollisionBox&& other) noexcept = delete;

	static std::vector<CCollisionBox*> m_pCollisionBoxes;
	std::vector<GameObject*> GetOverlappingObjects();

	void Update(float) override;

private:
	Rect m_Rect;
	bool m_IsOverlapEnabled = false;

	bool IsRectOverlapping(glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 topLeft2, glm::vec2 bottomRight2);
};
