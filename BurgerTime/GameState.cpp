#include "GameState.h"

void GameState::Notify(GameObject*, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		break;
	case Event::NPCKilled:
		break;
	case Event::BurgerCompleted:
		CheckPlayerVictory();
		break;
	}
}

void GameState::CheckPlayerVictory()
{
	std::cout << "Have I won?" << std::endl;

	//CHECK M_BOTTOM OF ALL BURGERS
}