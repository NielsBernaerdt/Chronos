#include "GameState.h"

void GameState::Notify(GameObject*, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		std::cout << "DEAD\n";
		break;
	case Event::NPCKilled:
		std::cout << "+100\n";
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