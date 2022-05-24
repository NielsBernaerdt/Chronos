#pragma once
#include "Chronos.h"

class BurgerTime : public Chronos
{
public:
	BurgerTime() = default;
	~BurgerTime() = default;
	BurgerTime(const BurgerTime& other) = delete;
	BurgerTime(BurgerTime&& other) noexcept = delete;
	BurgerTime& operator=(const BurgerTime& other) = delete;
	BurgerTime& operator=(BurgerTime&& other) noexcept = delete;

	void LoadGame() const override;
private:
	void TutorialScene(Scene& scene) const;
	void SceneGraphTestScene(Scene& scene) const;
};