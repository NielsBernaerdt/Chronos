#pragma once
#include <iostream>

#include "GameObject.h"
#include "BObserver.h"

enum class Event
{
	ActorDied
};

enum class Achievement
{
	FirstBlood
};

class Achievements : public BObserver
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
	void Unlock(Achievement achievement, GameObject*)
	{
		std::cout << "unlocked achievement: " << int(achievement) << std::endl;
	}
};