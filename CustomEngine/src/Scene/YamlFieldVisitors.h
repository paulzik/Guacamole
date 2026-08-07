#pragma once
#include "ECS/IFieldVisitor.h"
#include <yaml-cpp/yaml.h>

class YamlWriteVisitor : public IFieldVisitor {
public:
    explicit YamlWriteVisitor(YAML::Emitter& emitter) : out(emitter) {}

    bool IsReading() const override { return false; }

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

class YamlReadVisitor : public IFieldVisitor {
public:
    explicit YamlReadVisitor(const YAML::Node& source) : node(source) {}

    bool IsReading() const override { return true; }

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
