#include "Group.h"
#include "Geometry.h"
#include "Utility.h"
#include "Island.h"
#include "Ship.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>

using std::for_each;
using std::mem_fn; using std::bind;
using std::placeholders::_1; using std::ref;
using std::cout; using std::endl;
using std::shared_ptr;
using std::set;

// No need for update because it's members will update by themselves. Group don't have things to update for themselves.
void Group::update()
{
    //for_each(children.begin(), children.end(), mem_fn(&Component::update));
}


void Group::describe() const
{
    cout << "Group " << get_name() << " contains :";
    for_each(children.begin(), children.end(), [](shared_ptr<Component> component_ptr){cout << " "<< component_ptr->get_name();});
    cout << endl;
}

// No need for broadcast_current_state because group won't show on maps.
void Group::broadcast_current_state()
{
    //for_each(children.begin(), children.end(), mem_fn(&Component::broadcast_current_state));
}

void Group::set_destination_position_and_speed(Point destination_position, double speed)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->set_destination_position_and_speed(destination_position, speed);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}


void Group::set_course_and_speed(double course, double speed)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->set_course_and_speed(course, speed);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::stop()
{
    for (auto component_ptr : children) {
        try {
            component_ptr->stop();
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}


void Group::dock(shared_ptr<Island> island_ptr)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->dock(island_ptr);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::refuel()
{
    for (auto component_ptr : children) {
        try {
            component_ptr->refuel();
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::set_load_destination(shared_ptr<Island> island_ptr)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->set_load_destination(island_ptr);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::set_unload_destination(shared_ptr<Island> island_ptr)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->set_unload_destination(island_ptr);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::attack(shared_ptr<Ship> in_target_ptr)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->attack(in_target_ptr);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::stop_attack()
{
    for (auto component_ptr : children) {
        try {
            component_ptr->stop_attack();
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::set_terminus(Point position)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->set_terminus(position);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::add_component(shared_ptr<Component> component_ptr)
{
    children.insert(component_ptr);
}

void Group::remove_component(shared_ptr<Component> component_ptr)
{
    children.erase(component_ptr);
}

/*void Group::contain_component(shared_ptr<Component> component_ptr)
{
    set<shared_ptr<Component> > all_components;
    all_components.insert(component_ptr);
    component_ptr->get_all_contained_component(all_components);
    
    set<shared_ptr<Component> > my_all_components;
    get_all_contained_component(my_all_components);
    
    for (auto component_item : all_components) {
        if (component_item->get_name() == get_name() || my_all_components.find(component_item) != my_all_components.end()) {
            throw Error("Cannot add this component!");
        }
    }
}


void Group::get_all_contained_component(set<shared_ptr<Component> >& all_components)
{
    for (auto child : children) {
        all_components.insert(child);
        child->get_all_contained_component(all_components);
    }
}*/

