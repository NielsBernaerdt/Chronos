#pragma once
#include "CBase.h"

class CTransform final : public CBase
{
public:
	explicit CTransform(GameObject* gameObject, int x, int y);
	~CTransform() override = default;
	CTransform(const CTransform& other) = delete;
	CTransform(CTransform&& other) = delete;
	CTransform& operator=(const CTransform& other) = delete;
	CTransform& operator=(CTransform&& other) = delete;

	void SetPosition( int x, int y );
	const glm::vec3& GetPosition() const;
private:
	 glm::vec3 m_Transform;
};