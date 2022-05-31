#pragma once
#include <SDL.h>
/**
 * File containing Audio related structs used in AudioManager & ResourceManager
 */
struct WAV
{
	Uint32 length;
	Uint8* buffer;
	SDL_AudioSpec spec;
};

struct PlayMessage
{
	std::string id{};
	int volume{};
};

struct Audio
{
	static Uint8* audio_pos; // global pointer to the audio buffer to be played
	static Uint32 audio_len; // remaining length of the sample we have to play
	static void AudioCallBack(void* userdata, Uint8* stream, int len);
};