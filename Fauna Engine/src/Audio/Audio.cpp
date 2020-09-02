#include "Audio/Audio.h"
#include "Utility/Error.h"
#include "Utility/Util.h"
#include <wrl.h>

#define FAIL(hr) if (FAILED(hr)) return false;

using namespace Microsoft::WRL;

AudioEngine::~AudioEngine()
{
	pSourceReaderConfig->Release();
	pSourceReader->Release();
	MFShutdown();
	pMasterVoice->DestroyVoice();
	pAudio->StopEngine();
}

bool AudioEngine::Init()
{
	HRESULT hr = S_OK;
	hr = XAudio2Create(&pAudio, NULL, XAUDIO2_DEFAULT_PROCESSOR);
	THROW_IF_FAILED(hr, "Failed to init XAudio2.");
	
	hr = pAudio->CreateMasteringVoice(&pMasterVoice);
	THROW_IF_FAILED(hr, "Failed to create Master voice for XAudio2.");

	hr = MFStartup(MF_VERSION);
	THROW_IF_FAILED(hr, "MFStartup failed.");

	hr = MFCreateAttributes(&pSourceReaderConfig, 1);
	THROW_IF_FAILED(hr, "FAiled to create reader config.");

	hr = pSourceReaderConfig->SetUINT32(MF_LOW_LATENCY, true);
	THROW_IF_FAILED(hr, "Failed to set parameters");

	return true;
}

void AudioEngine::PlaySound2D(std::string filePath, bool looped)
{

}

bool AudioEngine::LoadFile(const std::wstring& filePath, std::vector<BYTE>& audioData, WAVEFORMATEX** wafeFormatEx, unsigned int& waveLength)
{
	HRESULT hr = S_OK;

	DWORD streamIndex = static_cast<DWORD>(MF_SOURCE_READER_FIRST_AUDIO_STREAM);

	if (pSourceReader != nullptr) {
		pSourceReader->Release();
	}
	hr = MFCreateSourceReaderFromURL(filePath.c_str(), pSourceReaderConfig, &pSourceReader);
	THROW_IF_FAILED(hr, "Failed to load audio file");
	if (FAILED(hr)) return false;
	//disable all other audio streams
	hr = pSourceReader->SetStreamSelection(static_cast<DWORD>(MF_SOURCE_READER_ALL_STREAMS), false);
	THROW_IF_FAILED(hr, "Failed to set stream selection.");
	if (FAILED(hr)) return false;
	//enable first audio stream
	hr = pSourceReader->SetStreamSelection(streamIndex, true);
	THROW_IF_FAILED(hr, "Failed to set stream selection.");
	if (FAILED(hr)) return false;

	//query info about the media file
	ComPtr<IMFMediaType> pMediaType = nullptr;
	hr = pSourceReader->GetNativeMediaType(streamIndex, 0, pMediaType.GetAddressOf());
	THROW_IF_FAILED(hr, "Failed to retrieve native media type.");
	if (FAILED(hr)) return false;

	//make sure that the file is an audio file
	GUID majorType = {};
	hr = pMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
	THROW_IF_FAILED(hr, "Failed to retrive GUID from file type.");
	if (majorType != MFMediaType_Audio)
		return false;

	//check for file compression
	GUID subType = {};
	hr = pMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType);
	if (subType == MFAudioFormat_Float || subType == MFAudioFormat_PCM)
	{
		//do nothing, uncompressed
	}
	else
	{
		//audio file is compressed bossman so we tell the 
		//source reader to decode and it looks for a way to do dat
		ComPtr<IMFMediaType> partialType = nullptr;
		hr = MFCreateMediaType(partialType.GetAddressOf());
		THROW_IF_FAILED(hr, "Create media type failed.");
		if (FAILED(hr)) return false;
		//set the media type to audio.
		hr = partialType->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
		THROW_IF_FAILED(hr, "Set GUID failed.");
		if (FAILED(hr)) return false;
		//request uncompressed data
		hr = partialType->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_PCM);
		THROW_IF_FAILED(hr, "Set GUID failed.");
		if (FAILED(hr)) return false;
	
		hr = pSourceReader->SetCurrentMediaType(streamIndex, nullptr, partialType.Get());
		THROW_IF_FAILED(hr, "Set media type failed.");
	}

	//uncompress the data and load it into a xaudio2 buffer
	ComPtr<IMFMediaType> uncompressedAudioType = nullptr;
	hr = pSourceReader->GetCurrentMediaType(streamIndex, uncompressedAudioType.GetAddressOf());
	THROW_IF_FAILED(hr, "get media type failed");



	return true;
}

void AudioEngine::PlaySound3D(SoundEffect& sound, float x, float y, 
	float z, bool looped)
{

}

/*AudioEngine::AudioEngine()
{
}

AudioEngine::~AudioEngine()
{
	//shutdown media foundation
	ReleaseCOM(pReaderConfig);
	ReleaseCOM(pSourceReader);
	MFShutdown();

	//destroy master voice
	pMasterVoice->DestroyVoice();
	//stop audio engine
	pAudioDevice->StopEngine();
	ReleaseCOM(pAudioDevice);//not sure if this is legal
}

bool AudioEngine::init()
{
	HRESULT hr = NULL;

	hr = MFStartup(MF_VERSION);
	if (FAILED(hr))
		return false;

	hr = MFCreateAttributes(&pReaderConfig, 1);
	if (FAILED(hr))
		return false;

	hr = pReaderConfig->SetUINT32(MF_LOW_LATENCY, true);
	if (FAILED(hr))
		return false;

	hr = XAudio2Create(&pAudioDevice);
	if (FAILED(hr))
		return false;

	hr = pAudioDevice->CreateMasteringVoice(&pMasterVoice);
	if (FAILED(hr))
		return false;

	return true;
}

void AudioEngine::start()
{
	pAudioDevice->StartEngine();
}

void AudioEngine::stop()
{
	pAudioDevice->StopEngine();
}

bool AudioEngine::loadFile(const std::wstring& filename, std::vector<BYTE>& audioData, WAVEFORMATEX** wafeFormatEx, unsigned int& waveLength)
{
	HRESULT hr = NULL;
	//locals !REMEMBER TO DESTROY!
	IMFMediaType* pMediaType = nullptr;
	
	hr = pSourceReader->SetStreamSelection(MF_SOURCE_READER_ALL_STREAMS, false);
	if (FAILED(hr))
		return false;
	hr = pSourceReader->SetStreamSelection(MF_SOURCE_READER_FIRST_AUDIO_STREAM, true);
	if (FAILED(hr))
		return false;

	hr = MFCreateSourceReaderFromURL(filename.c_str(), 
		pReaderConfig, &pSourceReader);
	if (FAILED(hr))
		return false;
	
	hr = pSourceReader->GetNativeMediaType(MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, &pMediaType);
	if (FAILED(hr))
		return false;

	GUID majorType{};
	hr = pMediaType->GetGUID(MF_MT_MAJOR_TYPE, &majorType);
	if (majorType != MFMediaType_Audio)
		return false;

	GUID subType{};
	hr = pMediaType->GetGUID(MF_MT_MAJOR_TYPE, &subType);
	if (subType == MFAudioFormat_Float || subType == MFAudioFormat_PCM)
	{

	}
	else
	{
		//
	}
	IMFMediaType* pAudioType = nullptr;


	ReleaseCOM(pMediaType);
	return true;
}*/


