#include "BObserver.h"
#include <iostream>
#include <GameObject.h>
#include "AudioManager.h"
#include "CPoints.h"
#include "HighScore.h"

void BObserver::Notify(GameObject* object, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
	{
		//AudioManager::GetInstance().PlaySound("DeathSound.wav", 30);
		std::cout << "PLAYER DIED\n";

		//todo somewhere else
		int points = dynamic_cast<CPoints*>(object->GetComponent<CPoints>())->GetPoints();
		WriteScoreToFile(points);
	}
		break;
	case Event::ActorDamaged:
		AudioManager::GetInstance().PlaySound("DamageSound.wav", 30);
		break;
	case Event::NPCKilled:
		AudioManager::GetInstance().PlaySound("KillEnemy.wav", 25);
		dynamic_cast<CPoints*>(object->GetComponent<CPoints>())->AddPoints(1000);
		break;
	case Event::BurgerCompleted:
		CheckPlayerVictory();
		break;
	}
}

void BObserver::CheckPlayerVictory()
{
	AudioManager::GetInstance().PlaySound("VictorySound.wav", 25);

	//WINCONDITION HERE
}