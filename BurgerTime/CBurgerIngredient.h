#pragma once
#include <CBase.h>
#include <memory>
#include <vector>

class Texture2D;

enum class Ingredient
{
	BunTop = 0,
	BunBottom = 1,
	Cheese = 2,
	Patty = 3,
	Tomato = 4,
	Lettuce = 5
};

class CBurgerIngredient : public CBase
{
public:
	CBurgerIngredient(GameObject* gameObject, Ingredient ingredient) : CBase(gameObject)
		, m_Ingredient(ingredient) {}
	~CBurgerIngredient() override = default;
	CBurgerIngredient(const CBurgerIngredient& other) = delete;
	CBurgerIngredient(CBurgerIngredient&& other) noexcept = delete;
	CBurgerIngredient& operator=(const CBurgerIngredient& other) = delete;
	CBurgerIngredient& operator=(CBurgerIngredient&& other) noexcept = delete;

	void Initialize() override;
	void Update(float) override;
	
	bool ReachedBottom() { return m_ReachedBottom; }

private:
	Ingredient m_Ingredient;
	int m_SideLength{ 8 };
	int m_Scale{ 24 };
	bool m_ReachedBottom{ false };

	std::vector<GameObject*> m_Children;
	std::vector<bool> m_IsTriggered;

	void SetTexture();
	void ResetPositions();
	void CheckPlayerCollision();
	bool IsOnPlate();
	void CheckForOtherIngredients();
};