#include "ChronosPCH.h"
#include "AudioManager.h"
#include <SDL_mixer.h>
#include "ResourceManager.h"

AudioManager::~AudioManager()
{
	m_ConditionThread.notify_one();
	m_AudioThread.join();
}

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

void AudioManager::PlaySound(std::string id, int volume, int loops)
{
	//Aggregation here
	for (size_t i = m_Head; i != m_Tail; i = (i + 1) % m_MaxPending)
	{
		if (m_PendingMessages[i]->GetId() == id)
		{
			m_PendingMessages[i]->SetVolume(std::max(volume, m_PendingMessages[i]->GetVolume()));
			return;
		}
	}
	assert((m_Tail + 1) % m_MaxPending != m_Head);

	m_PendingMessages[m_Tail] = ResourceManager::GetInstance().LoadAudioFile(id, volume, loops);
	m_Tail = (m_Tail + 1) % m_MaxPending;

	m_ConditionThread.notify_one();
}

void AudioManager::Update() //todo call this from dedicated audio thread
{
	do
	{
		if (m_LeaveThread == true)
			return;

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