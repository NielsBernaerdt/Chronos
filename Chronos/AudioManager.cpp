#include "ChronosPCH.h"
#include "AudioManager.h"
#include <SDL_mixer.h>
#include "ResourceManager.h"

void AudioManager::Init()
{
	m_Head = 0;
	m_Tail = 0;

	// Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "Error when calling Mix_OpenAudio: " << Mix_GetError() << std::endl;
	}

	m_AudioThread = std::thread{ &AudioManager::Update, this };
}

void AudioManager::PlaySound(std::string id, int volume)
{
	assert((m_Tail + 1) % m_MaxPending != m_Head);

	m_PendingMessages[m_Tail] = ResourceManager::GetInstance().LoadAudioFile(id, volume);
	m_Tail = (m_Tail + 1) % m_MaxPending;

	m_ConditionThread.notify_one();
}

void AudioManager::Update() //todo call this from dedicated audio thread
{
	do
	{
		if (m_Head != m_Tail)
		{
			m_PendingMessages[m_Head]->Play(0, (float)m_PendingMessages[m_Head]->GetVolume());

			m_Head = (m_Head + 1) % m_MaxPending;
		}

		std::unique_lock<std::mutex> lock{ m_AudioMutex };
		if(m_Head == m_Tail)
		{
			m_ConditionThread.wait(lock);
		}
	} while (m_Head != m_Tail);
}