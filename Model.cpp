#include "Model.h"
#include "Sim_object.h"
#include "Component.h"
#include "Island.h"
#include "Ship.h"
#include "View.h"
#include "Geometry.h"
#include <algorithm>
#include <functional>

using std::string;
using std::bind;
using std::placeholders::_1; using std::ref;
using std::map; using std::set;
using std::shared_ptr;
using std::for_each;

Model& Model::get_instance()
{
    static Model the_model;
    return the_model;
}

bool Model::is_name_in_use(const string& name) const
{
    return object_container.find(name.substr(0, 2)) != object_container.end();
}

bool Model::is_island_present(const string& name) const
{
    return island_container.find(name) != island_container.end();
}

void Model::add_island(shared_ptr<Island> new_island)
{
    island_container[new_island->get_name()] = new_island;
    object_container[new_island->get_name().substr(0, 2)] = new_island;
    new_island->broadcast_current_state();
}

shared_ptr<Island> Model::get_island_ptr(const string& name) const
{
    auto island_container_it = island_container.find(name);
    if (island_container_it == island_container.end())
        throw Error("Island not found!");
    return island_container_it->second;
}

bool Model::is_ship_present(const string& name) const
{
    return ship_container.find(name) != ship_container.end();
}

void Model::add_ship(shared_ptr<Ship> new_ship)
{
    add_component(new_ship);
    ship_container[new_ship->get_name()] = new_ship;
}

shared_ptr<Ship> Model::get_ship_ptr(const std::string& name) const
{
    auto ship_container_it = ship_container.find(name);
    if (ship_container_it == ship_container.end())
        throw Error("Ship not found!");
    return ship_container_it->second;
}


bool Model::is_component_present(const std::string& name) const
{
    return component_container.find(name) != component_container.end();
}

void Model::add_component(shared_ptr<Component> new_component)
{
    component_container[new_component->get_name()] = new_component;
    object_container[new_component->get_name().substr(0, 2)] = new_component;
    new_component->broadcast_current_state();
}

shared_ptr<Component> Model::get_component_ptr(const string& name) const
{
    auto component_container_it = component_container.find(name);
    if (component_container_it == component_container.end())
        throw Error("Component not found!");
    return component_container_it->second;
}

void Model::describe() const
{    
    for_each(object_container.begin(), object_container.end(),
             bind(&Sim_object::describe,
                  bind(& map<string, shared_ptr<Sim_object> >::value_type::second, _1)));
}

void Model::update()
{
    ++time;
    for_each(object_container.begin(), object_container.end(),
             bind(&Sim_object::update,
                  bind(& map<string, shared_ptr<Sim_object> >::value_type::second, _1)));
}

void Model::attach(shared_ptr<View> view)
{
    view_container.insert(view);
    for_each(object_container.begin(), object_container.end(),
             bind(&Sim_object::broadcast_current_state,
                  bind(& map<string, shared_ptr<Sim_object> >::value_type::second, _1)));
}

void Model::detach(shared_ptr<View> view)
{
    view_container.erase(view);
}

void Model::notify_location(const std::string& name, Point location)
{
    for_each(view_container.begin(), view_container.end(),
             bind(&View::update_location, _1, ref(name), ref(location)));
}

void Model::notify_fuel(const std::string& name, double fuel)
{
    for_each(view_container.begin(), view_container.end(),
             bind(&View::update_fuel, _1, ref(name), ref(fuel)));
}

void Model::notify_course(const std::string& name, double course)
{
    for_each(view_container.begin(), view_container.end(),
             bind(&View::update_course, _1, ref(name), ref(course)));
}


void Model::notify_speed(const std::string& name, double speed)
{
    for_each(view_container.begin(), view_container.end(),
             bind(&View::update_speed, _1, ref(name), ref(speed)));
}


void Model::notify_gone(const std::string& name)
{
    for_each(view_container.begin(), view_container.end(),
             bind(&View::update_remove, _1, ref(name)));
}

void Model::notify_destination(const std::string& name, Point destination)
{
    for_each(view_container.begin(), view_container.end(),
             bind(&View::update_destination, _1, ref(name), ref(destination)));
}


void Model::remove_component(shared_ptr<Component> component_ptr)
{
    ship_container.erase(component_ptr->get_name());
    component_container.erase(component_ptr->get_name());
    object_container.erase(component_ptr->get_name().substr(0, 2));
}

set<shared_ptr<Island>, Sim_object_comp> Model::get_all_islands() const
{
    set<shared_ptr<Island>, Sim_object_comp> all_islands;
    for (auto& map_pair : island_container)
        all_islands.insert(map_pair.second);
    return all_islands;
}

set<shared_ptr<Ship>, Sim_object_comp> Model::get_all_ships() const
{
    set<shared_ptr<Ship>, Sim_object_comp> all_ships;
    for (auto& map_pair : ship_container)
        all_ships.insert(map_pair.second);
    return all_ships;
}

set<shared_ptr<Component>, Sim_object_comp> Model::get_all_components() const
{
    set<shared_ptr<Component>, Sim_object_comp> all_components;
    for (auto& map_pair : component_container)
        all_components.insert(map_pair.second);
    return all_components;
}
