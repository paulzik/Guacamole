#pragma once
#include <string>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
#include <glm/vec4.hpp>
#include <glm/gtc/quaternion.hpp>

class IFieldVisitor {
public:
    virtual ~IFieldVisitor() = default;

    virtual bool IsReading() const = 0;

    virtual void Visit(const char* name, bool& value) = 0;
    virtual void Visit(const char* name, int& value) = 0;
    virtual void Visit(const char* name, float& value) = 0;
    virtual void Visit(const char* name, std::string& value) = 0;

    virtual void Visit(const char* name, glm::vec2& value) = 0;
    virtual void Visit(const char* name, glm::vec3& value) = 0;
    virtual void Visit(const char* name, glm::vec4& value) = 0;
    virtual void Visit(const char* name, glm::quat& value) = 0;
};
