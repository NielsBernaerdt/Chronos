#include "CBurgerIngredient.h"
#include "GameObject.h"

#include "GameState.h"
#include "CCollisionBox.h"
#include "CRender.h"
#include "CollisionGroups.h"
#include "CTransform.h"

void CBurgerIngredient::Initialize()
{
	for (const auto e : m_OwnerObject->GetChildren())
	{
		m_Children.push_back(e);
		m_IsTriggered.push_back(false);
		m_pChildRender.push_back(dynamic_cast<CRender*>(e->GetComponent<CRender>()));
		m_pChildCollision.push_back(dynamic_cast<CCollisionBox*>(e->GetComponent<CCollisionBox>()));
	}

	m_pTransform = m_OwnerObject->GetTransform();

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
		auto pos = m_pTransform->GetPosition();
		pos.y += m_FallingSpeed * deltaTime;
		m_pTransform->SetPosition(pos);
	}
}

void CBurgerIngredient::SetTexture()
{
	int index{};
	for (const auto& e : m_pChildRender)
	{
		glm::vec2 bottomLeft{};
		bottomLeft.x = float(index * m_SideLength);
		bottomLeft.y = float(int(m_Ingredient) * m_SideLength);
		Rect src{ (int)bottomLeft.x, (int)bottomLeft.y, m_SideLength, m_SideLength };

		e->SetSourceRect(src);

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
		auto pos = m_pTransform->GetPosition();
		pos.y += 1.3f * m_Children[0]->GetTransform()->GetScale().y;
		m_pTransform->SetPosition(pos);

		int index{};
		for (const auto& child : m_Children)
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

	for(size_t i{}; i < m_Children.size(); ++i)
	{
		if(m_IsTriggered[i] == false)
		{
			if(m_pChildCollision[i]->GetOverlappingObjects(CollisionGroup::Pawn).size() >= 1)
			{
				m_IsTriggered[i] = true;

				glm::vec3 pos{};
				pos.x += i * m_Children[i]->GetTransform()->GetScale().x;
				pos.y += 1.3f * m_Children[i]->GetTransform()->GetScale().y;

				m_Children[i]->GetTransform()->SetPosition(pos);

				ResetPositions();
			}
		}
	}
}

bool CBurgerIngredient::IsOnPlate()
{
	for(const auto& childCollision : m_pChildCollision)
	{
		//CHECK FOR PLATE
		if (childCollision->GetOverlappingObjects(CollisionGroup::Plate).size() >= 1)
		{
			m_ReachedBottom = true;
			return true;
		}
		//CHECK FOR GROUND
		if (childCollision->GetOverlappingObjects(CollisionGroup::Ground).size() >= 1)
		{
			return true;
		}
		//CHECK FOR OTHER BURGERS (ALREADY ON PLATE)
		const auto &otherBurgers = childCollision->GetOverlappingObjects(CollisionGroup::Burger);
		if (otherBurgers.size() >= 1)
		{
			if (dynamic_cast<CBurgerIngredient*>(otherBurgers[0]->GetParent()->GetComponent<CBurgerIngredient>())->ReachedBottom())
			{
				//NOTIFY OBSERVER
				if (m_Ingredient == Ingredient::BunTop)
				{
					m_OwnerObject->Notify(m_OwnerObject, Event::BurgerCompleted);

					m_ReachedBottom = true;
					return true;
				}
			}
		}
	}
	return false;
}

void CBurgerIngredient::CheckForOtherIngredients()
{
	if (m_Children.size() == 0)
		return;
	
	const auto& vector = m_pChildCollision[0]->GetOverlappingObjects(CollisionGroup::Burger);


	for(const auto& overlap : vector)
	{
		if (overlap->GetParent() != m_OwnerObject)
		{
			auto pos = overlap->GetParent()->GetTransform()->GetPosition();
			pos.y += 1.3f * m_Scale;
			overlap->GetParent()->GetTransform()->SetPosition(pos);
			return;
		}
	}

}