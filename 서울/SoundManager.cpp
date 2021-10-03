#include "DXUT.h"
#include "SoundManager.h"

Sound::Sound( std::wstring path, int szSound)
{
	static int IDX = 0;
	soundIDX = ++IDX;
	this->szSound = szSound;

	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];

		wsprintf(buffer, L"open %s alias %d_%d", path.c_str(), soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
		wsprintf(buffer, L"play %d_%d from 0", soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
		wsprintf(buffer, L"stop %d_%d", soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

void Sound::Play( bool loop)
{
	WCHAR buffer[256];
	wsprintf(buffer, L"play %d_%d from 0 %s", soundIDX, curSound, (loop) ? L"repeat" : L"");
	mciSendString(buffer, 0, 0, 0);
	if (++curSound >= szSound) curSound = 0;
}

void Sound::Stop()
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];
		wsprintf(buffer, L"stop %d_%d", soundIDX, i);
		mciSendString(buffer, 0, 0, 0);
	}
}

void Sound::SetVolume(int volume, std::wstring dir)
{
	for (int i = 0; i < szSound; ++i)
	{
		WCHAR buffer[256];
		wsprintf(buffer, L"setaudio %d_%d %s volume to %d", soundIDX, i, dir.c_str(), volume);
		mciSendString(buffer, 0, 0, 0);
	}
}

void SoundManager::Create(std::string name, std::wstring path, int szSound)
{
	auto sf = sounds.find(name);

	if (sf != sounds.end()) return;
	sounds.insert(std::make_pair(name, new Sound(path, szSound)));
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
		sf->second->SetVolume(volume, dir);
}
