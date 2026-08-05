#include "YamlFieldVisitors.h"

// ---------------------------------------------------------------- writing

void YamlWriteVisitor::Visit(const char* name, bool& value)
{
    out << YAML::Key << name << YAML::Value << value;
}

void YamlWriteVisitor::Visit(const char* name, int& value)
{
    out << YAML::Key << name << YAML::Value << value;
}

void YamlWriteVisitor::Visit(const char* name, float& value)
{
    out << YAML::Key << name << YAML::Value << value;
}

void YamlWriteVisitor::Visit(const char* name, std::string& value)
{
    out << YAML::Key << name << YAML::Value << value;
}

void YamlWriteVisitor::Visit(const char* name, glm::vec2& value)
{
    out << YAML::Key << name << YAML::Value << YAML::Flow
        << YAML::BeginSeq << value.x << value.y << YAML::EndSeq;
}

void YamlWriteVisitor::Visit(const char* name, glm::vec3& value)
{
    out << YAML::Key << name << YAML::Value << YAML::Flow
        << YAML::BeginSeq << value.x << value.y << value.z << YAML::EndSeq;
}

void YamlWriteVisitor::Visit(const char* name, glm::vec4& value)
{
    out << YAML::Key << name << YAML::Value << YAML::Flow
        << YAML::BeginSeq << value.x << value.y << value.z << value.w << YAML::EndSeq;
}

void YamlWriteVisitor::Visit(const char* name, glm::quat& value)
{
    // Stored x, y, z, w - glm's quat constructor takes (w, x, y, z).
    out << YAML::Key << name << YAML::Value << YAML::Flow
        << YAML::BeginSeq << value.x << value.y << value.z << value.w << YAML::EndSeq;
}

// ---------------------------------------------------------------- reading

void YamlReadVisitor::Visit(const char* name, bool& value)
{
    if (const YAML::Node field = node[name])
        value = field.as<bool>();
}

void YamlReadVisitor::Visit(const char* name, int& value)
{
    if (const YAML::Node field = node[name])
        value = field.as<int>();
}

void YamlReadVisitor::Visit(const char* name, float& value)
{
    if (const YAML::Node field = node[name])
        value = field.as<float>();
}

void YamlReadVisitor::Visit(const char* name, std::string& value)
{
    if (const YAML::Node field = node[name])
        value = field.as<std::string>();
}

void YamlReadVisitor::Visit(const char* name, glm::vec2& value)
{
    const YAML::Node field = node[name];
    if (!field || field.size() < 2)
        return;

    value = glm::vec2(field[0].as<float>(), field[1].as<float>());
}

void YamlReadVisitor::Visit(const char* name, glm::vec3& value)
{
    const YAML::Node field = node[name];
    if (!field || field.size() < 3)
        return;

    value = glm::vec3(field[0].as<float>(), field[1].as<float>(), field[2].as<float>());
}

void YamlReadVisitor::Visit(const char* name, glm::vec4& value)
{
    const YAML::Node field = node[name];
    if (!field || field.size() < 4)
        return;

    value = glm::vec4(field[0].as<float>(), field[1].as<float>(),
                      field[2].as<float>(), field[3].as<float>());
}

void YamlReadVisitor::Visit(const char* name, glm::quat& value)
{
    const YAML::Node field = node[name];
    if (!field || field.size() < 4)
        return;

    value = glm::quat(field[3].as<float>(),  // w
                      field[0].as<float>(),  // x
                      field[1].as<float>(),  // y
                      field[2].as<float>()); // z
}
