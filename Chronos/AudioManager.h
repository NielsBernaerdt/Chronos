#pragma once
#include "Singleton.h"
#include "Audio.h"

class AudioManager : public Singleton<AudioManager>
{
public:
	void Init();
	void PlaySound(std::string id, int volume);
	void Update();

private:
	static constexpr int m_MaxPending = 16;
	PlayMessage m_PendingMessages[m_MaxPending]{};
	int m_Head{};
	int m_Tail{};

	void OpenAudioDevice(WAV resource);
};