#include "Component.h"
#include "Utility.h"

using std::shared_ptr;

void Component::add_component(shared_ptr<Component> component_ptr)
{
    throw Error("Cannot add component!");
}

void Component::remove_component(shared_ptr<Component> component_ptr)
{
    throw Error("Cannot remove component!");
}

void Component::disband()
{
    throw Error("Cannot disband!");
}

void Component::check_contain_component(shared_ptr<Component> component_ptr)
{
    if (component_ptr->get_name() == get_name())
        throw Error("Cannot add this component!");
}
