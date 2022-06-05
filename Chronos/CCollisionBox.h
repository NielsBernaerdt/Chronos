#pragma once
#include "CBase.h"
#include "Rect.h"
#include "ChronosPCH.h"

enum class CollisionGroup;

class CCollisionBox : public CBase
{
public:
	CCollisionBox(GameObject* gameObject, CollisionGroup group, bool m_UseScale = true, Rect sizeREct = {0,0,0,0});
	~CCollisionBox() override = default;
	CCollisionBox(const CCollisionBox& other) = delete;
	CCollisionBox(CCollisionBox&& other) noexcept = delete;
	CCollisionBox& operator=(const CCollisionBox& other) = delete;
	CCollisionBox& operator=(CCollisionBox&& other) noexcept = delete;

	static std::vector<CCollisionBox*> m_pCollisionBoxes;
	std::vector<GameObject*> GetOverlappingObjects(CollisionGroup filter) const;
	CollisionGroup GetCollisionGroup() const { return m_CollisionGroup; }

	void Initialize() override;
	void Update(float) override;

private:
	bool m_UseScale{ true };
	Rect m_Rect{ 0,0,0,0 };
	CollisionGroup m_CollisionGroup;

	bool IsRectOverlapping(glm::vec2 topLeft, glm::vec2 bottomRight, glm::vec2 topLeft2, glm::vec2 bottomRight2) const;
};
