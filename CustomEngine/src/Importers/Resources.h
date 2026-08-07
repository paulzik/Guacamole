#pragma once
#include <memory>
#include <string>
#include <filesystem>
#include <unordered_map>
class Asset;

class Resources
{
private:
    inline static std::filesystem::path s_BasePath;    // project root
    inline static std::filesystem::path s_EnginePath;  // engine root

    inline static std::unordered_map<std::string, std::shared_ptr<Asset>> s_Cache;

public:
    static constexpr const char* EngineScheme = "engine://";

    static std::shared_ptr<Asset> Load(const std::string& path);

    template<typename T>
    static std::shared_ptr<T> Load(const std::string& path)
    {
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
