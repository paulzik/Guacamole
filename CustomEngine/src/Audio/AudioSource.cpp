#include "AudioSource.h"
#include "Utilities/Debug/Debug.h"
#include "ECS/Transform.h"
#include "ECS/Entity.h"

AudioSource::AudioSource()
{
}

AudioSource::~AudioSource()
{
	if (source != 0)
		alDeleteSources(1, &source);
}

bool AudioSource::GetLoop() const
{
	return loop;
}

float AudioSource::GetPitch() const
{
	return pitch;
}

float AudioSource::GetVolume() const
{
	return volume;
}

std::shared_ptr<AudioClip> AudioSource::GetAudioClip() const
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

void AudioSource::Start()
{
	std::cout << "STARTED" << std::endl;
}

void AudioSource::Update()
{
	if (!owner)
		return;

	if (!transform)
	{
		transform = &owner->GetComponent<Transform>();
		if (!transform)
		{
			std::cerr << "AudioSource: Owner has no Transform!" << std::endl;
			return;
		}
	}

	currentPosition = transform->position;

	if (currentPosition != prevPosition)
	{
		// Only update OpenAL if source exists
		if (source != 0)
		{
			alSource3f(source, AL_POSITION,
				currentPosition.x,
				currentPosition.y,
				currentPosition.z);
		}

		prevPosition = currentPosition;
	}
}



void AudioSource::Play()
{
	if (!clip) {
		Debug::LogError("AudioSource: No AudioClip set");
		return;
	}

	if (source == 0) {
		std::cout << "HERE" << std::endl;
		alGenSources(1, &source);
	}

	alSourcei(source, AL_BUFFER, clip->GetBuffer());
	alSourcef(source, AL_GAIN, volume);
	alSourcef(source, AL_PITCH, pitch);
	alSourcei(source, AL_LOOPING, loop ? AL_TRUE : AL_FALSE);
	
	alSource3f(source, AL_POSITION, currentPosition.x, currentPosition.y, currentPosition.z);

	alSourcef(source, AL_REFERENCE_DISTANCE, 1.0f);
	alSourcef(source, AL_MAX_DISTANCE, 50.0f);
	alSourcef(source, AL_ROLLOFF_FACTOR, 1.0f);

	alSourcePlay(source);
}

void AudioSource::Stop()
{
	if (source != 0) {
		alSourceStop(source);
	}
}

void AudioSource::Pause()
{
	if (source != 0) {
		alSourcePause(source);
	}
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


