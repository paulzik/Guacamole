#include "Animation.h"


void Animation::Play()
{
}

void Animation::AddPositionKey(int boneIndex, float time, const glm::vec3& position)
{
    if (boneIndex >= positions.size()) {
        positions.resize(boneIndex + 1);
    }
    positions[boneIndex].push_back({ time, position });
}

// Example: for rotation keyframes
void Animation::AddRotationKey(int boneIndex, float time, const glm::quat& rotation)
{
    if (boneIndex >= rotations.size()) {
        rotations.resize(boneIndex + 1);
    }
    rotations[boneIndex].push_back({ time, rotation });
}

// Example: for scale keyframes
void  Animation::AddScaleKey(int boneIndex, float time, const glm::vec3& scale)
{
    if (boneIndex >= scales.size()) {
        scales.resize(boneIndex + 1);
    }
    scales[boneIndex].push_back({ time, scale });
}

std::string Animation::GetAnimationName()
{
    return name;
}

float Animation::GetSpeed()
{
    return speed;
}

float Animation::GetDuration()
{
    return 0.0f;
}

glm::vec3 Animation::GetInterpolatedPosition(int boneIndex, float time) const
{
    if (boneIndex >= positions.size() || positions[boneIndex].empty())
        return glm::vec3(0.0f);

    const auto& keys = positions[boneIndex];

    // Before first key
    if (time <= keys.front().first) return keys.front().second;

    // After last key
    if (time >= keys.back().first) return keys.back().second;

    // Find the two keys surrounding 'time'
    for (size_t i = 0; i < keys.size() - 1; ++i)
    {
        if (time < keys[i + 1].first)
        {
            float t0 = keys[i].first;
            float t1 = keys[i + 1].first;
            const glm::vec3& p0 = keys[i].second;
            const glm::vec3& p1 = keys[i + 1].second;
            float factor = (time - t0) / (t1 - t0);
            return glm::mix(p0, p1, factor); // linear interpolation
        }
    }

    return keys.back().second; // fallback
}

glm::quat Animation::GetInterpolatedRotation(int boneIndex, float time) const
{
    if (boneIndex >= rotations.size() || rotations[boneIndex].empty())
        return glm::quat();

    const auto& keys = rotations[boneIndex];

    if (time <= keys.front().first) return keys.front().second;
    if (time >= keys.back().first) return keys.back().second;

    for (size_t i = 0; i < keys.size() - 1; ++i)
    {
        if (time < keys[i + 1].first)
        {
            float t0 = keys[i].first;
            float t1 = keys[i + 1].first;
            const glm::quat& r0 = keys[i].second;
            const glm::quat& r1 = keys[i + 1].second;
            float factor = (time - t0) / (t1 - t0);
            return glm::slerp(r0, r1, factor); // spherical linear interpolation
        }
    }

    return keys.back().second;
}

glm::vec3 Animation::GetInterpolatedScale(int boneIndex, float time) const
{
    if (boneIndex >= scales.size() || scales[boneIndex].empty())
        return glm::vec3(1.0f);

    const auto& keys = scales[boneIndex];

    if (time <= keys.front().first) return keys.front().second;
    if (time >= keys.back().first) return keys.back().second;

    for (size_t i = 0; i < keys.size() - 1; ++i)
    {
        if (time < keys[i + 1].first)
        {
            float t0 = keys[i].first;
            float t1 = keys[i + 1].first;
            const glm::vec3& s0 = keys[i].second;
            const glm::vec3& s1 = keys[i + 1].second;
            float factor = (time - t0) / (t1 - t0);
            return glm::mix(s0, s1, factor); // linear interpolation
        }
    }

    return keys.back().second;
}