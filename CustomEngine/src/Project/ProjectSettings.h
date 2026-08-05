#pragma once
#include <filesystem>
#include <string>


class ProjectSettings
{
public:
    static ProjectSettings& Get();

    // Loads a project.yaml. rootPath becomes the folder containing that file,
    // so a project keeps working when it is moved, copied or cloned.
    bool Load(const std::filesystem::path& projectFile);

    // Falls back to an empty, unnamed project rooted at the given folder.
    void UseFolder(const std::filesystem::path& folder);

    const std::filesystem::path& GetRootPath() const { return rootPath; }
    const std::string& GetName() const { return name; }
    const std::filesystem::path& GetStartupScene() const { return startupScene; }

private:
    // Runtime only
    std::filesystem::path rootPath;

    // relative to rootPath.
    std::string name;
    std::filesystem::path startupScene;
};
