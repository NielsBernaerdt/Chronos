#include "ChronosPCH.h"
#include "Audio.h"

void my_audio_callback(void* userdata, Uint8* stream, int len);
static Uint8* audio_pos; // global pointer to the audio buffer to be played
static Uint32 audio_len; // remaining length of the sample we have to play

void Audio::Initialize()
{
	m_Head = 0;
	m_Tail = 0;

	if(SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		std::cout << "ERROR AUDIO::INITIALIZE\n";
	}
}

void Audio::PlaySound(SoundId id, int volume)
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

void Audio::Update() //todo call this from dedicated audio thread
{
	if (m_Head == m_Tail) return;

	WAV resource = LoadSound(m_PendingMessages[m_Head].id);
	OpenAudioDevice(resource);

	m_Head = (m_Head + 1) % m_MaxPending;
}

WAV Audio::LoadSound(SoundId id)
{
	WAV params;
	if (SDL_LoadWAV(id.c_str(), &params.spec, &params.buffer, &params.length) == NULL)
	{
		std::cout << "ERROR AUDIO::UPDATE\n";
	}

	// set the callback function
	params.spec.callback = my_audio_callback;
	params.spec.userdata = NULL;
	// set our global static variables
	audio_pos = params.buffer; // copy sound buffer
	audio_len = params.length; // copy file length

	return params;
}

void Audio::OpenAudioDevice(WAV resource)
{
	if (SDL_OpenAudio(&resource.spec, NULL) < 0) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
		//exit(-1);
	}
	
	SDL_PauseAudio(0);

	// wait until we're don't playing
	while (audio_len > 0) {
		std::cout << "Audio Length: " << audio_len << std::endl;
		SDL_Delay(100);
	}

	// shut everything down
	SDL_CloseAudio();
	SDL_FreeWAV(resource.buffer);
}

void my_audio_callback(void*, Uint8* stream, int len) {

	if (audio_len == 0)
		return;

	len = (Uint32(len) > audio_len ? audio_len : len);
	SDL_memcpy (stream, audio_pos, len); 					// simply copy from one buffer into the other
	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}