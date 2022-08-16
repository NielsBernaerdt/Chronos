#pragma once
#include "CBase.h"

class CPoints : public CBase
{
public:
	CPoints(GameObject* gameObject) : CBase(gameObject) {}
	~CPoints() override = default;
	CPoints(const CPoints& other) = delete;
	CPoints(CPoints&& other) noexcept = delete;
	CPoints& operator=(const CPoints& other) = delete;
	CPoints& operator=(CPoints&& other) noexcept = delete;

	void SetPoints(int points) { m_Points = points; }
	int GetPoints() const { return m_Points; }
	void AddPoints(int value) { m_Points += value; }
private:
	int m_Points{};
};