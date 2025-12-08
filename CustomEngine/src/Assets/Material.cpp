#include "Material.h"
#include <memory>

Material::Material(std::shared_ptr<Shader> s) : shader(s) {};

Material::Material(std::shared_ptr<Texture2D> a, std::shared_ptr<Texture2D> n, std::shared_ptr<Shader> s) : albedo(a), normal(n), shader(s) {};