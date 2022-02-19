#pragma once
#include "CBase.h"
#include "Transform.h"

class CTransform final : public CBase
{
public:
	explicit CTransform(std::shared_ptr<GameObject> gameObject, const Transform& pos);
	virtual ~CTransform() = default;
	CTransform(const CTransform& other) = delete;
	CTransform(CTransform&& other) = delete;
	CTransform& operator=(const CTransform& other) = delete;
	CTransform& operator=(CTransform&& other) = delete;

	void SetPosition( const Transform& pos );
	const Transform& GetPosition() const;
private:
	Transform m_Transform;
};