#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/mat4x4.hpp>
#include <glm/ext/quaternion_float.hpp>

struct Bone {
    std::string name;
    int parentIndex;
    glm::mat4 localBindPose; // Initial local transform from aiNode
    glm::mat4 offsetMatrix;  // The Inverse Bind Pose from aiBone (Crucial!)

    glm::mat4 localTransform;  // Current animated local transform
    glm::mat4 globalTransform; // Current animated global transform
};

class Skeleton
{
public:
    Skeleton() = default;
    ~Skeleton() = default;
    int AddBone(const std::string& name, int parentIndex, const glm::mat4& localBindPose);
    int GetBoneIndex(const std::string& name) const;
    const Bone& GetBone(int index) const;
    int GetBoneCount() const;
    std::vector<int> GetRootBones() const;

    void SetLocalBoneTransform(int boneIndex, const glm::mat4& localTransform);
    void ComputeGlobalTransforms();

    const std::vector<Bone>& GetBones() const;
    void SetBoneOffset(int index, const glm::mat4& offset) {
        if (index >= 0 && index < bones.size()) {
            bones[index].offsetMatrix = offset;
        }
    }
private:
    std::vector<Bone> bones;
    std::unordered_map<std::string, int> nameToIndex;
};
