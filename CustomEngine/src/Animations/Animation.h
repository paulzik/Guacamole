#pragma once
#include "Assets/Asset.h"
#include <memory>


class Animation : public Asset
{
private:
	float speed = 1;
	bool isPlaying = false;
	float currentTime = 0.0f;

public:
	void Play();
	void Stop();
};