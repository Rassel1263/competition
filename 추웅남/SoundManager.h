#pragma once

class Sound
{
public:
	int soundIDX = 0;
	int szSound = 0;
	int curSound = 0;

	Sound(std::wstring path, int szSound, int volume);

	void Play(bool loop);
	void Stop();
	void Resume();
	void OnOff(bool on);
	void SetVolume(std::wstring dir, int volume);
};

class SoundManager : public Singleton<SoundManager>
{
private:
	std::map<std::string, Sound*> sounds;

public:
	void Create(std::string name, std::wstring path, int szSound, int volume = 500);
	void Play(std::string name, bool loop = false);
	void Stop(std::string name);
	void StopAll();
	void ToggleVolume();
	void SetVolume(std::string name, std::wstring dir, int volume);
};

