#include "Group.h"
#include "Geometry.h"
#include "Utility.h"
#include "Island.h"
#include "Ship.h"
#include <algorithm>
#include <functional>
#include <iostream>

using std::for_each;
using std::mem_fn;
using std::cout; using std::endl;

void Group::update()
{
    for_each(children.begin(), children.end(), mem_fn(&Component::update));
}

void Group::describe() const
{
    for_each(children.begin(), children.end(), mem_fn(&Component::describe));
}

void Group::broadcast_current_state()
{
    for_each(children.begin(), children.end(), mem_fn(&Component::broadcast_current_state));
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
    children.insert(component_ptr);
}

void Group::remove_component(std::shared_ptr<Component> component_ptr)
{
    children.erase(component_ptr);
}

