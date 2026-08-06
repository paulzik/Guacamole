#include "SceneSerializer.h"
#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "YamlFieldVisitors.h"
#include "Utilities/Debug/Debug.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <filesystem>
#include <vector>

bool SceneSerializer::Serialize(const std::filesystem::path& path) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Version" << YAML::Value << 1;
    out << YAML::Key << "Scene" << YAML::Value << path.stem().string();

    out << YAML::Key << "Entities" << YAML::Value << YAML::BeginSeq;
    
    
    for (const auto& e : Scene::Get().GetEntities())
    {
        out << YAML::BeginMap;
        out << YAML::Key << "Id" << YAML::Value << e->GetEntityID();
        out << YAML::Key << "Name" << YAML::Value << e->GetName();
        out << YAML::Key << "Parent" << YAML::Value<< (e->GetParent() ? e->GetParent()->GetEntityID() : 0);

        out << YAML::Key << "Components" << YAML::Value << YAML::BeginMap;
        for (const auto& c : e->GetAllComponents())
        {
            out << YAML::Key << c->GetComponentName() << YAML::Value << YAML::BeginMap;
            YamlWriteVisitor writer(out);
            c->Reflect(writer);

            out << YAML::EndMap;
        }
        out << YAML::EndMap;

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