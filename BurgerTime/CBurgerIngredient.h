#pragma once
#include <CBase.h>

enum class Ingredient
{
	BunTop		= 0,
	BunBottom	= 1,
	Cheese		= 2,
	Patty		= 3,
	Tomato		= 4,
	Lettuce		= 5
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
	int m_SideLength{ 8 };
	int m_Index;
	bool m_HasBeenTriggered = false;

	void SetTexture();
};