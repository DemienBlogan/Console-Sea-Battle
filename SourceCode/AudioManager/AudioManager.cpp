#include "AudioManager.h"
#include <fstream>

AudioManager& AudioManager::GetReference()
{
	static AudioManager manager;
	return manager;
}

void AudioManager::Initialize()
{
	InitializeDirectXTK();
	ReadAudioSettingsFromFile();
}

void AudioManager::Update()
{
	audioEngine->Update();
}

AudioManager::~AudioManager()
{
	audioEngine->Reset();
}

void AudioManager::InitializeDirectXTK()
{
	using namespace DirectX;
	using std::make_unique;

	// Initialize the COM library for use by the calling thread, 
	// set the thread's concurrency model, 
	// and create a new apartment for the thread if one is required.
	HRESULT result = CoInitializeEx(nullptr, COINIT_MULTITHREADED); // use 'result' for debugging cases

	// Initialize audio engine:
	AUDIO_ENGINE_FLAGS flags = AudioEngine_Default;
#ifdef _DEBUG
	flags |= AudioEngine_Debug;
#endif // DEBUG
	audioEngine = make_unique<AudioEngine>(flags);

	// Initialize audio:
	backgroundMenuMusic = make_unique<SoundEffect>(audioEngine.get(), backgroundMenuMusicFileName.c_str());
	backgroundMenuMusicInstance = backgroundMenuMusic->CreateInstance();
	changeMenuItemSound = make_unique<SoundEffect>(audioEngine.get(), changeMenuItemSoundFileName.c_str());
	selectMenuItemSound = make_unique<SoundEffect>(audioEngine.get(), selectMenuItemSoundFileName.c_str());
}

void AudioManager::ReadAudioSettingsFromFile()
{
	std::wifstream fileStream(audioSettingsFileName);
	if (!fileStream.is_open())
	{
		WriteAudioSettingsToFile();
		return;
	}

	fileStream >> isMusicOn >> isSoundsOn;

	fileStream.close();
}

void AudioManager::WriteAudioSettingsToFile()
{
	std::wofstream fileStream(audioSettingsFileName);

	// To read two bool-values normally, we need to put a delimeter between them.
	fileStream << isMusicOn << ' ' << isSoundsOn;

	fileStream.close();
}

void AudioManager::StopMusic()
{
	backgroundMenuMusicInstance->Stop();
}

bool AudioManager::PlayMusic(Audio music, bool loop)
{
	if (!isMusicOn)
	{
		return false;
	}

	switch (music)
	{
	case Audio::BackgroundMenuMusic:
		backgroundMenuMusicInstance->Play(loop);
		break;
	}

	return true;
}

bool AudioManager::PlaySound(Audio sound)
{
	if (!isSoundsOn)
	{
		return false;
	}

	switch (sound)
	{
	case Audio::ChangeMenuItemSound:
		changeMenuItemSound->Play();
		break;

	case Audio::SelectMenuItemSound:
		selectMenuItemSound->Play();
		break;
	}

	return true;
}