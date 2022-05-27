#pragma once
#include <iostream>

//todo remove
#include "CPoints.h"
//
#include "GameObject.h"
#include "Observer.h"

enum class Event
{
	ActorDied
};

enum class Achievement
{
	FirstBlood
};

class Achievements : public Observer
{
public:
	void Notify(GameObject* object, Event event) override
	{
		switch(event)
		{
		case Event::ActorDied:
			Unlock(Achievement::FirstBlood, object);
			break;
		}
	}
private:
	void Unlock(Achievement achievement, GameObject* object)
	{
		std::cout << "unlocked achievement: " << int(achievement) << std::endl;

		dynamic_cast<CPoints*>(object->GetComponent<CPoints>().get())->SetPoints(200);
	}
};