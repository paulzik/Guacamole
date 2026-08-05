#pragma once
#include "ECS/IFieldVisitor.h"
#include <yaml-cpp/yaml.h>

// Writes each visited field as a key/value pair into the emitter.
class YamlWriteVisitor : public IFieldVisitor {
public:
    explicit YamlWriteVisitor(YAML::Emitter& emitter) : out(emitter) {}

    void Visit(const char* name, bool& value) override;
    void Visit(const char* name, int& value) override;
    void Visit(const char* name, float& value) override;
    void Visit(const char* name, std::string& value) override;

    void Visit(const char* name, glm::vec2& value) override;
    void Visit(const char* name, glm::vec3& value) override;
    void Visit(const char* name, glm::vec4& value) override;
    void Visit(const char* name, glm::quat& value) override;

private:
    YAML::Emitter& out;
};

// Reads each visited field from the node. Fields missing from the file are left at their current value
class YamlReadVisitor : public IFieldVisitor {
public:
    explicit YamlReadVisitor(const YAML::Node& source) : node(source) {}

    void Visit(const char* name, bool& value) override;
    void Visit(const char* name, int& value) override;
    void Visit(const char* name, float& value) override;
    void Visit(const char* name, std::string& value) override;

    void Visit(const char* name, glm::vec2& value) override;
    void Visit(const char* name, glm::vec3& value) override;
    void Visit(const char* name, glm::vec4& value) override;
    void Visit(const char* name, glm::quat& value) override;

private:
    const YAML::Node& node;
};
