#include "Group.h"
#include "Geometry.h"
#include "Utility.h"
#include "Island.h"
#include "Ship.h"
#include "Model.h"
#include <algorithm>
#include <functional>
#include <iostream>
#include <set>

using std::for_each;
using std::mem_fn; using std::bind;
using std::placeholders::_1; using std::ref;
using std::cout; using std::endl;
using std::shared_ptr; using std::weak_ptr;
using std::set;


void Group::update()
{
    auto it = children.begin();
    while (it != children.end()) {
        if (!it->second.lock())
            children.erase(it++);
        else
            ++it;
    }
}

void Group::describe() const
{
    cout << endl << "Group " << get_name() << " contains :";
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            cout << " "<< sp->get_name();
        }
    }
    cout << endl;
}

void Group::set_destination_position_and_speed(Point destination_position, double speed)
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->set_destination_position_and_speed(destination_position, speed);
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}


void Group::set_course_and_speed(double course, double speed)
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->set_course_and_speed(course, speed);
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::stop()
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->stop();
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}


void Group::dock(shared_ptr<Island> island_ptr)
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->dock(island_ptr);
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::refuel()
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->refuel();
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::set_load_destination(shared_ptr<Island> island_ptr)
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->set_load_destination(island_ptr);
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::set_unload_destination(shared_ptr<Island> island_ptr)
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->set_unload_destination(island_ptr);
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::attack(shared_ptr<Ship> in_target_ptr)
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->attack(in_target_ptr);
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::stop_attack()
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->stop_attack();
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::set_terminus(Point position)
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            try {
                sp->set_terminus(position);
            } catch (Error& error) {
                cout << sp->get_name() << "'s error message : " << error.what() << endl;
            }
        }
    }
}

void Group::add_component(shared_ptr<Component> child)
{
    weak_ptr<Component> component_weak_ptr(child);
    children[child->get_name()] = component_weak_ptr;
}

void Group::remove_component(shared_ptr<Component> child)
{
    if (children.find(child->get_name()) == children.end())
        throw Error("Component is not in the group!");
    children.erase(child->get_name());
}

void Group::disband()
{
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp) {
            Model::get_instance().remove_group_member(sp->get_name());
        }
    }
}

void Group::check_contain_component(std::shared_ptr<Component> component_ptr)
{
    if (component_ptr->get_name() == get_name())
        throw Error("Cannot add this component!");
    for (auto child : children) {
        shared_ptr<Component> sp = child.second.lock();
        if (sp)
            sp->check_contain_component(component_ptr);
    }
}
