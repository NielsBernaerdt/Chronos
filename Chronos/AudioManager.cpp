#include "ChronosPCH.h"
#include "AudioManager.h"
#include "ResourceManager.h"

void AudioManager::Init()
{
	m_Head = 0;
	m_Tail = 0;

	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "ERROR AUDIO::INITIALIZE\n";
	}
}

void AudioManager::PlaySound(std::string id, int volume)
{
	//either aggregate here, check for optimization -> maybe in update? since that's on a seperate thread
	for (size_t i = m_Head; i != m_Tail; i = (i + 1) % m_MaxPending)
	{
		if (m_PendingMessages[i].id == id)
		{
			m_PendingMessages[i].volume = std::max(volume, m_PendingMessages[i].volume);

			return;
		}
	}
	//
	assert((m_Tail + 1) % m_MaxPending != m_Head);
	
	m_PendingMessages[m_Tail].id = id;
	m_PendingMessages[m_Tail].volume = volume;
	m_Tail = (m_Tail + 1) % m_MaxPending;
}

void AudioManager::Update() //todo call this from dedicated audio thread
{
	if (m_Head == m_Tail) return;

	WAV resource = ResourceManager::GetInstance().LoadWAV(m_PendingMessages[m_Head].id);
	OpenAudioDevice(resource);

	m_Head = (m_Head + 1) % m_MaxPending;
}

void AudioManager::OpenAudioDevice(WAV resource)
{
	if (SDL_OpenAudio(&resource.spec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		//exit(-1);
	}
	
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while (Audio::audio_len > 0) {
		std::cout << "Audio Length: " << Audio::audio_len << std::endl;
		SDL_Delay(100);
	}

	// shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(resource.buffer);
}