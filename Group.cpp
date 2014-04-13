#include "Group.h"
#include "Geometry.h"
#include "Utility.h"
#include "Island.h"
#include "Ship.h"
#include <algorithm>
#include <functional>
#include <iostream>

using std::for_each;
using std::mem_fn; using std::bind;
using std::placeholders::_1; using std::ref;
using std::cout; using std::endl;
using std::shared_ptr;

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


void Group::dock(std::shared_ptr<Island> island_ptr)
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

void Group::set_load_destination(std::shared_ptr<Island> island_ptr)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->set_load_destination(island_ptr);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::set_unload_destination(std::shared_ptr<Island> island_ptr)
{
    for (auto component_ptr : children) {
        try {
            component_ptr->set_unload_destination(island_ptr);
        } catch (Error& error) {
            cout << component_ptr->get_name() << "'s error message : " << error.what() << endl;
        }
    }
}

void Group::attack(std::shared_ptr<Ship> in_target_ptr)
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


void Group::add_component(std::shared_ptr<Component> component_ptr)
{
    contain_component(component_ptr);
    children.insert(component_ptr);
}

void Group::remove_component(std::shared_ptr<Component> component_ptr)
{
    children.erase(component_ptr);
}

void Group::contain_component(std::shared_ptr<Component> component_ptr)
{
    Component::contain_component(component_ptr);
    for_each(children.begin(), children.end(), bind(&Component::contain_component, _1, ref(component_ptr)));
}




