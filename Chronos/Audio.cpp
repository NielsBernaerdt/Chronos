#include "ChronosPCH.h"
#include "Audio.h"

Uint8* Audio::audio_pos; // global pointer to the audio buffer to be played
Uint32 Audio::audio_len; // remaining length of the sample we have to play

void Audio::AudioCallBack(void*, Uint8* stream, int len)
{
	if (audio_len == 0)
		return;

	len = (Uint32(len) > audio_len ? audio_len : len);
	SDL_memcpy(stream, audio_pos, len); 					// simply copy from one buffer into the other
	//SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);// mix from one buffer into another

	audio_pos += len;
	audio_len -= len;
}