#include "MiniginPCH.h"
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"
#include "CBase.h"
#include "CText.h"
template <typename T>
GameObject<T>::~GameObject()
{
	for (auto e : m_pComponents)
	{
		delete e;
		e = nullptr;
	}
}

template <typename T>
void GameObject<T>::Update(float deltaTime)
{
	for (auto e : m_pComponents)
	{
		e->Update(deltaTime);
	}
}

template <typename T>
void GameObject<T>::Render() const
{
	for (auto e : m_pComponents)
	{
		e->Render();
	}
}

template <typename T>
void GameObject<T>::SetPosition(float x, float y)
{
	m_Transform.SetPosition(x, y, 0.0f);
}

template <typename T>
void GameObject<T>::AddComponent(CBase* component)
{
	m_pComponents.push_back(component);
}

template <typename T>
T GameObject<T>::GetComponent<T>() const
{
	for (auto e : m_pComponents)
	{
		CText* temp = dynamic_cast<CText*>(e);
		if (temp)
		{

		}
	}
}