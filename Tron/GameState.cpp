#include "GameState.h"
#include <iostream>
#include <GameObject.h>
#include "AudioManager.h"
#include "CPoints.h"
#include "HighScore.h"
#include "CTankNPC.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Tron.h"

void GameState::HandleEvent(GameObject* object, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
	{
		AudioManager::GetInstance().PlaySound("AudioFiles/DeathSound.wav", 30);
		int points = dynamic_cast<CPoints*>(object->GetComponent<CPoints>())->GetPoints();
		WriteScoreToFile(points);
		//Open score menu here
	}
	break;
	case Event::ActorDamaged:
		AudioManager::GetInstance().PlaySound("AudioFiles/DamageSound.wav", 30);
		break;
	case Event::NPCDamaged:
		AudioManager::GetInstance().PlaySound("AudioFiles/DamageSound.wav", 30);
		break;
	case Event::NPCKilled:
	{
		AudioManager::GetInstance().PlaySound("AudioFiles/KillEnemy.wav", 25);
		int points = dynamic_cast<CTankNPC*>(object->GetComponent<CTankNPC>())->GetPointsWorth();
		dynamic_cast<CPoints*>(m_pPlayerPawn->GetComponent<CPoints>())->AddPoints(points);
		CheckPlayerVictory();
	}
		break;
	}
}

void GameState::CheckPlayerVictory()
{
	if (CTankNPC::m_NrNPCsAlive - 1 <= 0)
	{
		AudioManager::GetInstance().PlaySound("AudioFiles/LevelComplete.wav", 30);

		//const int nrLevels{ 3 };
		//int currentSceneIdx = (SceneManager::GetInstance().GetActiveSceneIdx() + 1) % nrLevels;

		////reset current
		//SceneManager::GetInstance().GetActiveScene()->ClearScene();

		////interrupt update current
		//SceneManager::GetInstance().GetActiveScene()->InterruptUpdate();

		////open next
		//SceneManager::GetInstance().OpenScene(currentSceneIdx);
		////clear next
		//SceneManager::GetInstance().GetScene(currentSceneIdx)->ClearScene();

		////load new objects
		//Tron::LoadSceneByIndex(currentSceneIdx);
	}
}