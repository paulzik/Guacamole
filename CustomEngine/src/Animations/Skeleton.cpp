#include "Skeleton.h"
#include <glm/gtc/quaternion.hpp> 

int Skeleton::AddBone(const std::string& name, int parentIndex, const glm::mat4& offsetMatrix)
{
    int index = static_cast<int>(bones.size());
    bones.push_back({ name, parentIndex, offsetMatrix });
    nameToIndex[name] = index;
    return index;
}

int Skeleton::GetBoneIndex(const std::string& name) const
{
    auto it = nameToIndex.find(name);
    if (it != nameToIndex.end())
        return it->second;
    return -1;
}

const Bone& Skeleton::GetBone(int index) const 
{
    return bones[index]; 
}
int Skeleton::GetBoneCount() const 
{ 
    return static_cast<int>(bones.size()); 
}

std::vector<int> Skeleton::GetRootBones() const
{
    std::vector<int> roots;
    for (size_t i = 0; i < bones.size(); ++i)
    {
        if (bones[i].parentIndex == -1)
            roots.push_back(static_cast<int>(i));
    }
    return roots;
}

void Skeleton::SetLocalBoneTransform(int boneIndex, const glm::mat4& localTransform)
{
    bones[boneIndex].localTransform = localTransform;
}

void Skeleton::ComputeGlobalTransforms()
{
    for (size_t i = 0; i < bones.size(); ++i)
    {
        if (bones[i].parentIndex == -1)
        {
            bones[i].globalTransform = bones[i].localTransform;
        }
        else
        {
            bones[i].globalTransform = bones[bones[i].parentIndex].globalTransform * bones[i].localTransform;
        }
    }
}
