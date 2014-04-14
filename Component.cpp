#include "Component.h"
#include "Utility.h"


void Component::add_component(std::shared_ptr<Component> component_ptr)
{
    throw Error("Cannot add component!");
}

void Component::remove_component(std::shared_ptr<Component> component_ptr)
{
    throw Error("Cannot remove component!");
}

/*void Component::contain_component(std::shared_ptr<Component> component_ptr)
{
    if (component_ptr->get_name() == get_name())
        throw Error("Cannot add this component!");
}*/


