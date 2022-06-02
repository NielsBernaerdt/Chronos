#pragma once
#include <CBase.h>

enum class Ingredient
{
	BunTop,
	BunBottom,
	Patty,
	Cheese,
	Lettuce,
	Tomato
};

class CBurgerIngredient : public CBase
{
public:
	CBurgerIngredient(GameObject* gameObject, Ingredient ingredient, int index);
	~CBurgerIngredient() override = default;
	CBurgerIngredient(const CBurgerIngredient& other) = delete;
	CBurgerIngredient(CBurgerIngredient&& other) noexcept = delete;
	CBurgerIngredient& operator=(const CBurgerIngredient& other) = delete;
	CBurgerIngredient& operator=(CBurgerIngredient&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;

private:
	Ingredient m_Ingredient;
	int m_Index;
	int m_Up{};
	float m_Diff{20.f};
	float m_accTime{};
};