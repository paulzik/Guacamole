#pragma once
#include <memory>
#include <string>
#include <filesystem>
class Asset;

// Resolves asset paths against one of two roots:
//
//   "Assets/Models/Miner.fbx"          -> the open project's folder
//   "engine://Shaders/BasicVertex.vert"-> the engine's own files, next to the exe
//
// Engine code must use the engine:// form so it never depends on a project
// happening to contain a particular file.
class Resources
{
private:
    inline static std::filesystem::path s_BasePath;    // project root
    inline static std::filesystem::path s_EnginePath;  // engine root

public:
    static constexpr const char* EngineScheme = "engine://";

    static std::shared_ptr<Asset> Load(const std::string& path);

    template<typename T>
    static std::shared_ptr<T> Load(const std::string& path)
    {
        // path/name are filled in by the non-template Load, so every asset gets
        // them regardless of which overload was used.
        auto asset = Load(path);
        return std::dynamic_pointer_cast<T>(asset);
    }

    // Turns a project- or engine-relative path into an absolute one.
    static std::filesystem::path Resolve(const std::string& path);

    static void SetBasePath(const std::filesystem::path& path);
    static const std::filesystem::path& GetBasePath();

    static void SetEnginePath(const std::filesystem::path& path);
    static const std::filesystem::path& GetEnginePath();
};
