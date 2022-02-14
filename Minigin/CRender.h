#pragma once
#include "CBase.h"
#include "Transform.h"

class Texture2D;

class CRender final : public CBase
{
public:
	explicit CRender(std::shared_ptr<Texture2D> texture, Transform pos);
	virtual ~CRender() = default;
	CRender(const CRender& other) = delete;
	CRender(CRender&& other) = delete;
	CRender& operator=(const CRender& other) = delete;
	CRender& operator=(CRender&& other) = delete;

	void Render() const override;
	void SetTexture(std::shared_ptr<Texture2D> texture);
	void SetPosition(Transform pos);
private:
	std::shared_ptr<Texture2D> m_Texture;
	Transform m_Transform;
};