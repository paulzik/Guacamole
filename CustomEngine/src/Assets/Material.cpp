#include "Material.h"
#include <memory>

Material::Material(std::shared_ptr<Shader> s) : shader(s) {};