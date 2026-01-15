#include "AudioSource.h"
#include "Utilities/Debug/Debug.h"

AudioSource::AudioSource()
{
}

AudioSource::~AudioSource()
{
}

bool AudioSource::GetLoop()
{
	return loop;
}

float AudioSource::GetPitch()
{
	return pitch;
}

float AudioSource::GetVolume()
{
	return volume;
}

std::shared_ptr<AudioClip> AudioSource::GetAudioClip()
{
	return clip;
}

bool AudioSource::IsPlaying() const
{
	return false;
}

const char* AudioSource::GetComponentName() const
{
	return "AudioSource";
}

void AudioSource::Play()
{
	if (!clip) {
		Debug::LogError("AudioSource: No AudioClip set");
		return;
	}

	if (source == 0) {
		alGenSources(1, &source);
	}

	alSourcei(source, AL_BUFFER, clip->GetBuffer());
	alSourcef(source, AL_GAIN, volume);
	alSourcef(source, AL_PITCH, pitch);
	alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);

	alSourcePlay(source);
}

void AudioSource::Stop()
{
}

void AudioSource::Pause()
{
}

void AudioSource::SetLoop(bool _loop)
{
	loop = _loop;
}

void AudioSource::SetClip(std::shared_ptr<AudioClip> _clip)
{
	if (_clip == nullptr) {
		Debug::LogError("The clip is null");
		return;
	}

	clip = _clip;
}

void AudioSource::SetVolume(float _volume)
{
	if(_volume > 0)
		volume = _volume;
}

void AudioSource::SetPitch(float _pitch)
{
	if(_pitch > 0)
		pitch = _pitch;
}


