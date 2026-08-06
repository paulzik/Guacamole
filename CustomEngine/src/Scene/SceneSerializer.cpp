#include "SceneSerializer.h"
#include "ECS/Scene.h"
#include "ECS/Entity.h"
#include "ECS/Camera/Camera.h"
#include "Scenegraph/Scenegraph.h"
#include "YamlFieldVisitors.h"
#include "Utilities/Debug/Debug.h"
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <unordered_map>
#include <vector>

// Bumped whenever the scene format changes in a way older files cannot express.
static constexpr int SceneFileVersion = 1;

bool SceneSerializer::Serialize(const std::filesystem::path& path) {
    YAML::Emitter out;
    out << YAML::BeginMap;
    out << YAML::Key << "Version" << YAML::Value << SceneFileVersion;
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
    YAML::Node config;

    // Parse before touching the scene
    try
    {
        std::ifstream file(path);
        if (!file)
        {
            Debug::LogError("Scene file not found: " + path.generic_string());
            return false;
        }

        config = YAML::Load(file);
    }
    catch (const YAML::Exception& e)
    {
        Debug::LogError("Reading scene YAML error: " + std::string(e.what()));
        return false;
    }

    const int version = config["Version"] ? config["Version"].as<int>() : 0;
    if (version != SceneFileVersion)
    {
        Debug::LogWarning("Scene file version " + std::to_string(version) +
                          ", expected " + std::to_string(SceneFileVersion) +
                          " - loading anyway");
    }

    YAML::Node entities = config["Entities"];

    Scene::Get().Clear();

    // Maps the ids stored in the file to the entities just created, so the
    // second pass can resolve Parent references.
    std::unordered_map<uint64_t, Entity*> entitiesById;

    try
    {
        // ---- Pass 1: create every entity and fill its components ----
        for (const auto& entityNode : entities)
        {
            if (!entityNode["Id"] || !entityNode["Name"])
            {
                Debug::LogWarning("Skipping entity without an Id or Name");
                continue;
            }

            uint64_t id = entityNode["Id"].as<uint64_t>();
            const std::string name = entityNode["Name"].as<std::string>();

            // Position comes from the Transform component below, not from here.
            Entity* entity = nullptr;

            if (id == 0 || entitiesById.count(id) > 0)
            {
                Debug::LogWarning("Entity '" + name + "' has an invalid or duplicate id"
                                  " - assigning a new one");

                // The public overload generates a fresh id for us.
                entity = Scene::Get().CreateEntity(name, glm::vec3(0));
                id = entity->GetEntityID();
            }
            else
            {
                entity = Scene::Get().CreateEntity(name, glm::vec3(0), nullptr, id);
            }

            entitiesById[id] = entity;

            // Components is a YAML map: key = COMPONENT_NAME, value = its fields.
            for (const auto& component : entityNode["Components"])
            {
                const std::string componentName = component.first.as<std::string>();

                Component* created = entity->GetOrCreateComponent(componentName);
                if (!created)
                {
                    Debug::LogWarning("Unknown component '" + componentName +
                                      "' on entity '" + name + "'");
                    continue;
                }

                YamlReadVisitor reader(component.second);
                created->Reflect(reader);
            }
        }

        // ---- Pass 2: resolve the hierarchy ----
        Scenegraph& scenegraph = Scene::Get().GetScenegraph();

        for (const auto& entityNode : entities)
        {
            if (!entityNode["Id"] || !entityNode["Parent"])
                continue;

            const uint64_t parentId = entityNode["Parent"].as<uint64_t>();
            if (parentId == 0)
                continue; // stays a root

            auto childIt  = entitiesById.find(entityNode["Id"].as<uint64_t>());
            auto parentIt = entitiesById.find(parentId);

            if (childIt == entitiesById.end())
                continue;

            if (parentIt == entitiesById.end())
            {
                Debug::LogWarning("Entity '" + childIt->second->GetName() +
                                  "' references a parent that is not in the scene");
                continue;
            }

            scenegraph.RemoveEntity(childIt->second);
            scenegraph.AddEntity(childIt->second, parentIt->second);
        }
    }
    catch (const YAML::Exception& e)
    {
        Debug::LogError("Malformed scene data: " + std::string(e.what()));
        return false;
    }

    if (!Scene::Get().GetCamera())
    {
        for (const auto& entity : Scene::Get().GetEntities())
        {
            if (Camera* camera = entity->TryGetComponent<Camera>())
            {
                Scene::Get().AddCamera(camera);
                break;
            }
        }

        if (!Scene::Get().GetCamera())
            Debug::LogWarning("Loaded scene contains no Camera - nothing will render");
    }

    Scene::Get().Start();

    Debug::Log("Loaded scene " + path.generic_string() + " (" +
               std::to_string(entitiesById.size()) + " entities)");
    return true;
}