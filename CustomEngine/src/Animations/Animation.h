#pragma once
#include "Assets/Asset.h"
#include <glm/vec3.hpp>
#include <glm/gtc/quaternion.hpp>
#include <vector>
#include <utility>
#include <string>

class Animation : public Asset
{
public:
    Animation(const std::string& name, float duration)
        : name(name), duration(duration) {
    }

    // Keyframe storage
    void AddPositionKey(int boneIndex, float time, const glm::vec3& position);
    void AddRotationKey(int boneIndex, float time, const glm::quat& rotation);
    void AddScaleKey(int boneIndex, float time, const glm::vec3& scale);

    // Sampling
    bool HasChannel(int boneIndex) const;
    glm::vec3 GetInterpolatedPosition(int boneIndex, float time) const;
    glm::quat GetInterpolatedRotation(int boneIndex, float time) const;
    glm::vec3 GetInterpolatedScale(int boneIndex, float time) const;

    // Metadata
    float GetDuration() const;
    const std::string& GetAnimationName() const;

private:
    std::string name;
    float duration = 0.0f;

    std::vector<std::vector<std::pair<float, glm::vec3>>> positions;
    std::vector<std::vector<std::pair<float, glm::quat>>> rotations;
    std::vector<std::vector<std::pair<float, glm::vec3>>> scales;
};
