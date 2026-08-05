#include "SceneSerializer.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <filesystem>
#include "../ECS/Entity.h"
#include "../ECS/Scene.h"

bool SceneSerializer::Serialize(const std::filesystem::path& path) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Version" << YAML::Value << 1;
    out << YAML::Key << "Scene" << YAML::Value << path.stem().string();

    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
    
    
    for (Entity* e : Scene::Get().GetEntities())
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Id" << YAML::Value << e->GetEntityID();
        out << YAML::Key << "Name" << YAML::Value << e->GetName();
        out << YAML::Key << "Parent" << YAML::Value<< (e->GetParent() ? e->GetParent()->GetEntityID() : 0);

        // transform, components, parent UUID... go here
        out << YAML::EndMap;
    }
    
    
    out << YAML::EndSeq;
    out << YAML::EndMap;

    std::error_code ec;
    std::filesystem::create_directories(path.parent_path(), ec);

    std::ofstream file(path);
    if (!file) return false;

    file << out.c_str();
    return file.good();
}

bool SceneSerializer::DeSerialize(const std::filesystem::path& path) {

	return true;
}