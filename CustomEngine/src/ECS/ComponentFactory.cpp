#include "ComponentFactory.h"
#include "Component.h"

ComponentFactory& ComponentFactory::Instance()
{
    // Function-local static: constructed on first use, so it is always ready
    // before the COMPONENT_NAME registrations run during static initialisation.
    static ComponentFactory instance;
    return instance;
}

std::unique_ptr<Component> ComponentFactory::Create(const std::string& name) const
{
    auto it = creators.find(name);
    if (it == creators.end())
        return nullptr;

    return it->second();
}

bool ComponentFactory::IsRegistered(const std::string& name) const
{
    return creators.find(name) != creators.end();
}
