#include "DXUT.h"
#include "SoundManager.h"

Sound::Sound(std::wstring path, int szSound, int volume)
{
	static int IDX = 0;
	soundIDX = ++IDX;
	this->szSound = szSound;

	for (int i = 0; i < szSound; ++i)
	{
		WCHAR temp[256];
		wsprintf(temp, L"open %s alias %d_%d", path.c_str(), soundIDX, i);
		mciSendString(temp, 0, 0, 0);
		wsprintf(temp, L"setaudio %d_%d volume to %d", soundIDX, i, volume);
		mciSendString(temp, 0, 0, 0);
	}
}

void Sound::Play(bool loop)
{
	WCHAR temp[256];
	wsprintf(temp, L"play %d_%d from 0 %s", soundIDX, curSound, (loop) ? L"repeat" : L"");
	mciSendString(temp, 0, 0, 0);
	if (++curSound >= szSound) curSound = 0;
}

void Sound::Stop()
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR temp[256];
		wsprintf(temp, L"stop %d_%d", soundIDX, i);
		mciSendString(temp, 0, 0, 0);
	}
}

void Sound::SetVolume(std::wstring dir, int volume)
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR temp[256];
		wsprintf(temp, L"setaudio %d_%d %s volume to %d", soundIDX, i, dir.c_str(), volume);
		mciSendString(temp, 0, 0, 0);
	}
}

void SoundManager::Create(std::string name, std::wstring path, int szSound, int volume)
{
	auto sf = sounds.find(name);

	if (sf != sounds.end()) return;
	sounds.insert(std::make_pair(name, new Sound(path, szSound, volume)));
}

void SoundManager::Play(std::string name, bool loop)
{
	auto sf = sounds.find(name);

	if (sf != sounds.end())
		sf->second->Play(loop);
}

void SoundManager::Stop(std::string name)
{
	auto sf = sounds.find(name);

	if (sf != sounds.end())
		sf->second->Stop();
}

void SoundManager::StopAll()
{
	for (auto& sound : sounds)
		sound.second->Stop();
}

void SoundManager::SetVolume(std::string name, std::wstring dir, int volume)
{
	auto sf = sounds.find(name);

	if (sf != sounds.end())
		sf->second->SetVolume(dir, volume);
}
