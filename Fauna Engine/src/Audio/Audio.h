#pragma once

#include "Win.h"
#include <xaudio2.h>
#include <string>
#include <vector>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

class SoundEffect;

class AudioEngine
{
	friend class SoundEffect;
public:
	AudioEngine() = default;
	AudioEngine(const AudioEngine&) = delete;
	AudioEngine& operator=(const AudioEngine&) = delete;
	~AudioEngine();

	bool Init();
	void PlaySound2D(std::string filePath, bool looped = false);
	void PlaySound3D(SoundEffect& sound, float x, float y, 
		float z, bool looped = false);
private:
	bool LoadFile(const std::wstring& filePath, std::vector<BYTE>& audioData, WAVEFORMATEX** wafeFormatEx, unsigned int& waveLength);
	IMFAttributes* pSourceReaderConfig = nullptr;
	IMFSourceReader* pSourceReader = nullptr;
	IXAudio2* pAudio = nullptr;
	IXAudio2MasteringVoice* pMasterVoice = nullptr;
};

class SoundEffect 
{
public:

private:

};

/*class Sound
{
public:
	Sound(AudioEngine& engine, std::string filePath);
	~Sound();

	void setVolume(float volume);
	irrklang::ISoundSource* getSource() const { return source; }
private:
	irrklang::ISoundSource* source;
};*/
/*#include "Win.h"
#include <xaudio2.h>

#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>

#pragma comment(lib, "mfreadwrite.lib")
#pragma comment(lib, "mfplat.lib")
#pragma comment(lib, "mfuuid")

#include <string>
#include <vector>

/*class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	IXAudio2* getEffectDevice();
	IXAudio2MasteringVoice* getMusicVoice();

	bool init();
	void createDevice();
	void stop();
	void start();
	
private:
	bool audioAvailable;
	IXAudio2* pEffectDevice = nullptr;
	IXAudio2* pMusicDevice = nullptr;
	IXAudio2MasteringVoice* pEffectMasterVoice = nullptr;
	IXAudio2MasteringVoice* pMusicMasterVoice = nullptr;
};*/

/*class AudioEngine
{
public:
	AudioEngine();
	~AudioEngine();

	bool init();
	void start();
	void stop();
	bool loadFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** wafeFormatEx, unsigned int& waveLength);
private:
	IXAudio2* pAudioDevice = nullptr;
	IXAudio2MasteringVoice* pMasterVoice = nullptr;
	IMFAttributes* pReaderConfig = nullptr;
	IMFSourceReader* pSourceReader = nullptr;
};*/

