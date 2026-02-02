#include "AudioSource.h"
#include "Utilities/Debug/Debug.h"
#include "ECS/Transform.h"
#include "ECS/Entity.h"


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