#include "ProjectSettings.h"
#include <yaml-cpp/yaml.h>
#include <iostream>

ProjectSettings& ProjectSettings::Get()
{
    static ProjectSettings instance;
    return instance;
}

void ProjectSettings::UseFolder(const std::filesystem::path& folder)
{
    rootPath = folder;
    name = folder.filename().string();
    startupScene.clear();
}

bool ProjectSettings::Load(const std::filesystem::path& projectFile)
{
    if (!std::filesystem::exists(projectFile))
    {
        std::cerr << "[Project] No project file at: " << projectFile.string() << std::endl;
        return false;
    }

    // The project's location is where its file lives - it is never stored
    // inside the file, which would break as soon as the folder moved.
    rootPath = projectFile.parent_path();

    try
    {
        YAML::Node project = YAML::LoadFile(projectFile.string());

        if (project["Name"])
            name = project["Name"].as<std::string>();
        else
            name = rootPath.filename().string();

        if (project["StartupScene"])
            startupScene = project["StartupScene"].as<std::string>();
    }
    catch (const YAML::Exception& e)
    {
        std::cerr << "[Project] Failed to parse " << projectFile.string()
                  << ": " << e.what() << std::endl;
        return false;
    }

    std::cout << "[Project] Opened '" << name << "' at " << rootPath.string() << std::endl;
    return true;
}
