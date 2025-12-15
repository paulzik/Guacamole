#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <glm/mat4x4.hpp>
#include <glm/ext/quaternion_float.hpp>

struct Bone
{
    std::string name;      // bone name (from FBX)
    int parentIndex;       // -1 for root bone
    glm::mat4 offsetMatrix; // transforms from mesh space to bone space
    glm::mat4 localTransform;
    glm::mat4 globalTransform;
};

class Skeleton
{
public:
    Skeleton() = default;
    ~Skeleton() = default;

    int AddBone(const std::string& name, int parentIndex, const glm::mat4& offsetMatrix);
    int GetBoneIndex(const std::string& name) const;
    const Bone& GetBone(int index) const;
    int GetBoneCount() const;
    std::vector<int> GetRootBones() const;

    void SetLocalBoneTransform(int boneIndex, const glm::mat4& localTransform);
    void ComputeGlobalTransforms();


private:
    std::vector<Bone> bones;
    std::unordered_map<std::string, int> nameToIndex;
};
