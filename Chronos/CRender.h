#pragma once
#include "CBase.h"

class Texture2D;

class CRender final : public CBase
{
public:
	explicit CRender(GameObject* gameObject, std::shared_ptr<Texture2D> texture, bool scaleToObject = false);
	~CRender() override = default;
	CRender(const CRender& other) = delete;
	CRender(CRender&& other) = delete;
	CRender& operator=(const CRender& other) = delete;
	CRender& operator=(CRender&& other) = delete;

	void Initialize() override;
	void Render() const;
	void SetTexture(std::shared_ptr<Texture2D> texture);
private:
	std::shared_ptr<Texture2D> m_Texture{};
	bool m_ScaleToObject{};
	glm::vec3 m_Scale{};
};