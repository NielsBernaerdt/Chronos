#pragma once
#include "Singleton.h"
#include <SDL.h>
//todo make this
using SoundId = std::string;

struct PlayMessage
{
	SoundId id;
	int volume;
};

struct WAV
{
	Uint32 length;
	Uint8* buffer;
	SDL_AudioSpec spec;
};

class Audio : public Singleton<Audio>
{
public:
	void Initialize();
	void PlaySound(SoundId id, int volume);
	void Update();

private:
	static constexpr int m_MaxPending = 16;
	PlayMessage m_PendingMessages[m_MaxPending];
	int m_Head;
	int m_Tail;

	WAV LoadSound(SoundId id);
	void OpenAudioDevice(WAV resource);
};