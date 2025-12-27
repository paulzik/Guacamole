#include "AudioClip.h"

AudioClip::AudioClip(const std::string& path)
{

}

AudioClip::~AudioClip() = default;

ALuint AudioClip::GetBuffer() const 
{
	return buffer;
}


