#include "GameState.h"
#include <GameObject.h>
#include <AudioManager.h>
#include <SceneManager.h>
#include <Scene.h>
#include "CPoints.h"
#include "HighScore.h"
#include "CTankNPC.h"
#include "Tron.h"

void GameState::HandleEvent(GameObject* pObject, Event event)
{
	switch (event)
	{
	case Event::ActorDied:
		HandlePlayerDeath();
		break;
	case Event::ActorDamaged:
		AudioManager::GetInstance().PlaySound("AudioFiles/DamageSound.wav", 30);
		break;
	case Event::NPCDamaged:
		AudioManager::GetInstance().PlaySound("AudioFiles/DamageSound.wav", 30);
		break;
	case Event::NPCKilled:
		HandleNPCDeath(pObject);
		break;
	}
}

void GameState::CheckPlayerVictory()
{
	if (CTankNPC::m_NrNPCsAlive - 1 <= 0)
	{
		AudioManager::GetInstance().PlaySound("AudioFiles/LevelComplete.wav", 30);

		const int nrLevels{ 3 };
		int currentSceneIdx = (SceneManager::GetInstance().GetActiveSceneIdx() + 1) % nrLevels;

		//reset current
		SceneManager::GetInstance().GetActiveScene()->ClearScene();

		//open next
		SceneManager::GetInstance().OpenScene(currentSceneIdx);
		//clear next
		SceneManager::GetInstance().GetScene(currentSceneIdx)->ClearScene();

		//load new objects
		Tron::LoadSceneByIndex(currentSceneIdx);
	}
}

void GameState::HandlePlayerDeath()
{
	AudioManager::GetInstance().PlaySound("AudioFiles/DeathSound.wav", 30);
	int points = dynamic_cast<CPoints*>(m_pPlayerPawn->GetComponent<CPoints>())->GetPoints();
	WriteScoreToFile(points);
	SceneManager::GetInstance().GetActiveScene()->ClearScene();
	SceneManager::GetInstance().OpenScene(3);
	SceneManager::GetInstance().GetScene(3)->ClearScene();
	Tron::LoadScoreMenu();
}

void GameState::HandleNPCDeath(GameObject* pGameObject)
{
	AudioManager::GetInstance().PlaySound("AudioFiles/KillEnemy.wav", 25);
	int points = dynamic_cast<CTankNPC*>(pGameObject->GetComponent<CTankNPC>())->GetPointsWorth();
	dynamic_cast<CPoints*>(m_pPlayerPawn->GetComponent<CPoints>())->AddPoints(points);
	CheckPlayerVictory();
}