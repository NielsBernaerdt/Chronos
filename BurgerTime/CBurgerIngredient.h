#pragma once
#include <CBase.h>

#include <vector>

class CCollisionBox;
class CRender;
class CTransform;
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

	CTransform* m_pTransform = nullptr;
	int m_FallingSpeed = 70;

	std::vector<GameObject*> m_Children;
	std::vector<bool> m_IsTriggered;
	std::vector<CRender*> m_pChildRender;
	std::vector<CCollisionBox*> m_pChildCollision;

	void SetTexture();
	void ResetPositions();
	void CheckPlayerCollision();
	bool IsOnPlate();
	void CheckForOtherIngredients();
};