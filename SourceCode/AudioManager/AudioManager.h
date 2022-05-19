#pragma once
#include <Audio.h>

#undef PlaySound // I can't name my method 'PlaySound' because file 'Windows.h' already has this macro. So I undef it.

enum class Audio
{
	BackgroundMenuMusic,
	ChangeMenuItemSound,
	SelectMenuItemSound
};

class AudioManager
{
private:
	const std::wstring audioSettingsFileName = L"Resources/Data/AudioSettings.bin";
	const std::wstring backgroundMenuMusicFileName = L"Resources/Audio/BackgroundMenuMusic.wav";
	const std::wstring changeMenuItemSoundFileName = L"Resources/Audio/ChangeMenuItemSound.wav";
	const std::wstring selectMenuItemSoundFileName = L"Resources/Audio/SelectMenuItemSound.wav";

	std::unique_ptr<DirectX::AudioEngine> audioEngine;

	std::unique_ptr<DirectX::SoundEffect> backgroundMenuMusic;
	std::unique_ptr<DirectX::SoundEffectInstance> backgroundMenuMusicInstance;

	std::unique_ptr<DirectX::SoundEffect> changeMenuItemSound;
	std::unique_ptr<DirectX::SoundEffect> selectMenuItemSound;


	bool isMusicOn = true;  // default value
	bool isSoundsOn = true; // default value

	AudioManager() = default;
	AudioManager(const AudioManager&) = delete;
	AudioManager& operator=(const AudioManager&) = delete;

	void InitializeDirectXTK();

public:
	static AudioManager& GetInstance();
	
	~AudioManager();

	void Initialize();
	void Update();
	
	bool IsMusicOn() const { return isMusicOn; }
	bool IsSoundsOn() const { return isSoundsOn; }
	void TurnOnMusic() { isMusicOn = true; }
	void TurnOffMusic() { isMusicOn = false; }
	void TurnOnSounds() { isSoundsOn = true; }
	void TurnOffSounds() { isSoundsOn = false; }

	void StopMusic();
	bool PlayMusic(Audio music, bool loop);
	bool PlaySound(Audio sound);

	void ReadAudioSettingsFromFile();
	void WriteAudioSettingsToFile();
};