#include "GameState.h"
#include <iostream>

#include "AudioManager.h"
#include "CPoints.h"

void GameState::Notify(GameObject*, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		AudioManager::GetInstance().PlaySound("DeathSound.wav", 30);
		std::cout << "PLAYER DIED\n";
		break;
	case Event::ActorDamaged:
		AudioManager::GetInstance().PlaySound("DamageSound.wav", 30);
		break;
	case Event::NPCKilled:
		AudioManager::GetInstance().PlaySound("KillEnemy.wav", 25);
		dynamic_cast<CPoints*>(m_pPawn->GetComponent<CPoints>())->GivePoints(1000);
		break;
	case Event::BurgerCompleted:
		CheckPlayerVictory();
		break;
	}
}

void GameState::CheckPlayerVictory()
{
	AudioManager::GetInstance().PlaySound("VictorySound.wav", 25);

	//WINCONDITION HERE
}