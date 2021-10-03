#pragma once

class Sound
{
public:
	int soundIDX = 0;
	int curSound = 0;
	int szSound = 0;

	Sound(std::wstring path, int szSound);

	void Play( bool loop);
	void Stop();
	void SetVolume(int volume, std::wstring dir);
};

class SoundManager  : public Singleton<SoundManager>
{
private:
	std::map<std::string, Sound*> sounds;

public:
	void Create(std::string name, std::wstring path, int szSound);
	void Play(std::string name, bool loop = false);
	void Stop(std::string name);
	void StopAll();
	void SetVolume(std::string, std::wstring dir, int volume);
};

