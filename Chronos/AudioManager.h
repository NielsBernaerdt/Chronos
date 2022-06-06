#pragma once
#include <future>
#include "Singleton.h"

class SoundEffect;

class AudioManager : public Singleton<AudioManager>
{
public:
	~AudioManager() override;

	void Init();
	void PlaySound(std::string id, int volume, int loops = 0);
	void Update();

	void LeaveThread(bool b) { m_LeaveThread = b; }

private:
	static constexpr int m_MaxPending = 16;
	SoundEffect* m_PendingMessages[m_MaxPending]{};
	int m_Head{};
	int m_Tail{};
	bool m_LeaveThread = false;

	std::mutex m_AudioMutex{};
	std::thread m_AudioThread;
	std::condition_variable m_ConditionThread;
};
