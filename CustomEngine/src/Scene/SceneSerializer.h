#pragma once
#include <filesystem>

class Scene; // forward declared - including Scene.h here would be circular

class SceneSerializer {
public:
	static bool Serialize(const std::filesystem::path& path);
	static bool DeSerialize(const std::filesystem::path& path);
};