#pragma once
#include <future>
#include "Singleton.h"

class SoundEffect;

class AudioManager : public Singleton<AudioManager>
{
public:
	void Init();
	void PlaySound(std::string id, int volume, int loops = 0);
	void Update();

private:
	static constexpr int m_MaxPending = 16;
	SoundEffect* m_PendingMessages[m_MaxPending]{};
	int m_Head{};
	int m_Tail{};

	std::mutex m_AudioMutex{};
	std::thread m_AudioThread;
	std::condition_variable m_ConditionThread;
};
