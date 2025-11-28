#pragma once
#include <memory>
#include <string>
#include <filesystem>
class Asset;

class Resources
{
private:
    inline static std::filesystem::path s_BasePath = std::filesystem::current_path().parent_path();

public:
    static std::shared_ptr<Asset> Load(const std::string& path);

    static void SetBasePath(const std::filesystem::path& path);
    static const std::filesystem::path& GetBasePath();
};
