#pragma once
#include "Assets/Asset.h"
#include <memory>
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <utility>

class Animation : public Asset
{
private:
	float speed = 1;
	bool isPlaying = false;
	float currentTime = 0.0f;
	float duration = 0.0f;
	std::string name;
	bool loop = true;

	std::vector<std::vector<std::pair<float, glm::vec3>>> positions;   // per bone
	std::vector<std::vector<std::pair<float, glm::quat>>> rotations;    // per bone
	std::vector<std::vector<std::pair<float, glm::vec3>>> scales;       // per bone

public:
	Animation(const std::string& _name, const float _duration)
		: name(_name), duration(_duration) {
	}

	void Play();
	void Stop();

	void AddPositionKey(int boneIndex, float time, const glm::vec3& position);
	void AddRotationKey(int boneIndex, float time, const glm::quat& rotation);
	void AddScaleKey(int boneIndex, float time, const glm::vec3& scale);

	std::string GetAnimationName();
	float GetSpeed();
	float GetDuration();

	glm::vec3 GetInterpolatedPosition(int boneIndex, float time) const;
	glm::quat GetInterpolatedRotation(int boneIndex, float time) const;
	glm::vec3 GetInterpolatedScale(int boneIndex, float time) const;
};