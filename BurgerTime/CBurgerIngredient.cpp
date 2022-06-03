#include "CBurgerIngredient.h"
#include "GameObject.h"
#include <string>
#include "CCollisionBox.h"
#include "CRender.h"
#include "CollisionGroups.h"
#include "CTransform.h"

std::vector<std::shared_ptr<GameObject>> CBurgerIngredient::ConstructChildren(std::shared_ptr<Texture2D> texture)
{
	constexpr size_t nrBurgerParts{ 4 };
	constexpr int scale{ 24 };
	for (size_t i{}; i < nrBurgerParts; ++i)
	{
		const auto child = std::make_shared<GameObject>(std::string{ "PattyChild" + i });
		child->GetTransform()->SetPosition((int)i * scale, 0);
		child->GetTransform()->SetScale(scale, scale);
		const auto pattyChild0Collision = std::make_shared<CCollisionBox>(child.get(), CollisionGroup::Burger);
		child->AddComponent(pattyChild0Collision);
		const auto patty0child0CRender = std::make_shared<CRender>(child.get(), texture, true);
		child->AddComponent(patty0child0CRender);
		m_Children.push_back(child);
		m_IsTriggered.push_back(false);
	}

	return m_Children;
}

void CBurgerIngredient::Initialize()
{
	SetTexture();
}

void CBurgerIngredient::Update(float deltaTime)
{
	if (IsFalling())
	{
		auto transform = m_OwnerObject->GetTransform();

		auto pos = transform->GetPosition();
		pos.y += 70 * deltaTime;

		transform->SetPosition(pos);
		transform->UpdateRelativeTransform();
	}
	else
	{
		int i{};
		for (auto e : m_Children)
		{
			if (m_IsTriggered[i] == false)
			{
				CCollisionBox* box = dynamic_cast<CCollisionBox*>(e->GetComponent<CCollisionBox>().get());
				if (box->GetOverlappingObjects(CollisionGroup::Pawn).size() >= 1)
				{
					m_IsTriggered[i] = true;

					glm::vec3 pos{};
					pos.x += i * e->GetTransform()->GetScale().x;
					pos.y += e->GetTransform()->GetScale().y / 2;

					e->GetTransform()->SetPosition(pos);
				}
			}
			++i;
		}
	}
}

void CBurgerIngredient::SetTexture()
{
	int index{};
	for (auto e : m_Children)
	{
		glm::vec2 bottomLeft{};
		bottomLeft.x = float(index * m_SideLength);
		bottomLeft.y = float(int(m_Ingredient) * m_SideLength);
		Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SideLength, m_SideLength };

		dynamic_cast<CRender*>(e->GetComponent<CRender>().get())->SetSourceRect(src);

		++index;
	}
}

bool CBurgerIngredient::IsFalling()
{
	for (bool b : m_IsTriggered)
	{
		if (b == false) return false;
	}
	return true;
}