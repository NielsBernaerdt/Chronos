#pragma once
#pragma warning(push, 0)
#include <glm/glm.hpp>
#pragma warning (pop)
#include "CBase.h"

class CTransform final : public CBase
{
public:
	explicit CTransform(GameObject* gameObject, int x = 0, int y = 0);
	~CTransform() override = default;
	CTransform(const CTransform& other) = delete;
	CTransform(CTransform&& other) = delete;
	CTransform& operator=(const CTransform& other) = delete;
	CTransform& operator=(CTransform&& other) = delete;

	void SetPosition( int x, int y );
	void SetPosition(glm::vec3 pos);
	const glm::vec3& GetPosition();

	void SetScale(int x, int y);
	void SetScale(glm::vec3 scale);
	const glm::vec3& GetScale() const;

	void SetDirty(bool isDirty) { m_IsDirty = isDirty; }
	bool IsDirty() const { return m_IsDirty; }

	void UpdateRelativeTransform();
private:
	bool m_IsDirty = true;
	glm::vec3 m_Pos{};
	glm::vec3 m_WorldPos{};

	glm::vec3 m_Scale{50, 50, 1};
};