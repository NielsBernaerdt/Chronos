#include "CBurgerIngredient.h"
#include "GameObject.h"
#include <string>
#include "CCollisionBox.h"
#include "CRender.h"
#include "CollisionGroups.h"
#include "CPlate.h"
#include "CTransform.h"

std::vector<std::shared_ptr<GameObject>> CBurgerIngredient::ConstructChildren(std::shared_ptr<Texture2D> texture)
{
	constexpr size_t nrBurgerParts{ 4 };
	for (size_t i{}; i < nrBurgerParts; ++i)
	{
		const auto child = std::make_shared<GameObject>(std::string{ "PattyChild" + i });
		child->GetTransform()->SetPosition((int)i * m_Scale, 0);
		child->GetTransform()->SetScale(m_Scale, m_Scale);
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
	if(IsOnPlate())
	{
		CheckPlayerCollision();
	}
	else
	{
		CheckForOtherIngredients();

		//FALLING CALCULATIONS
		auto transform = m_OwnerObject->GetTransform();
		auto pos = transform->GetPosition();
		pos.y += 70 * deltaTime;
		transform->SetPosition(pos);
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

void CBurgerIngredient::ResetPositions()
{
	bool shouldReset = true;
	for (bool b : m_IsTriggered)
	{
		if (b == false) shouldReset = false;
	}

	if (shouldReset == true)
	{
		auto pos = m_OwnerObject->GetTransform()->GetPosition();
		pos.y += 1.2f * m_Children[0]->GetTransform()->GetScale().y;
		m_OwnerObject->GetTransform()->SetPosition(pos);

		int index{};
		for (auto child : m_Children)
		{
			child->GetTransform()->SetPosition(index * m_Scale, 0);
			++index;
		}


		for(int i{}; i < m_IsTriggered.size(); ++i)
		{
			m_IsTriggered[i] = false;
		}
	}
}

void CBurgerIngredient::CheckPlayerCollision()
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
				pos.y += 1.2f * e->GetTransform()->GetScale().y ;

				e->GetTransform()->SetPosition(pos);

				ResetPositions();
			}
		}
		++i;
	}
}

bool CBurgerIngredient::IsOnPlate()
{
	for(auto child : m_Children)
	{
		auto collisionbox = dynamic_cast<CCollisionBox*>(child->GetComponent<CCollisionBox>().get());
		auto overlappingObjects = collisionbox->GetOverlappingObjects(CollisionGroup::Plate);
		if(overlappingObjects.size() >= 1)
		{
			if (dynamic_cast<CPlate*>(overlappingObjects[0]->GetComponent<CPlate>().get())->IsFinalPlate() == true)
			{
				m_ReachedBottom = true;
			}
			return true;
		}
	}
	return false;
}

void CBurgerIngredient::CheckForOtherIngredients()
{
	auto collisionboxChild = dynamic_cast<CCollisionBox*>(m_Children[0]->GetComponent<CCollisionBox>().get());
	auto vector = collisionboxChild->GetOverlappingObjects(CollisionGroup::Burger);


	for(auto overlap : vector)
	{
		if (overlap->GetParent().get() != m_OwnerObject)
		{
			auto pos = overlap->GetParent()->GetTransform()->GetPosition();
			pos.y += 1.2f * m_Scale;
			overlap->GetParent()->GetTransform()->SetPosition(pos);
			return;
		}
	}

}