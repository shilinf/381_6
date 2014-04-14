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

// No need for update because it's members will update by themselves. Group don't have things to update for themselves.
void Group::update()
{
    //for_each(children.begin(), children.end(), mem_fn(&Component::update));
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

// No need for broadcast_current_state because group won't show on maps.
void Group::broadcast_current_state()
{
    //for_each(children.begin(), children.end(), mem_fn(&Component::broadcast_current_state));
}

void Group::set_destination_position_and_speed(Point destination_position, double speed)
{
    for (auto child : children) {
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
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
        shared_ptr<Component> sp = check_get_component(child.second);
        if (sp) {
            Model::get_instance().remove_group_member(sp->get_name());
        }
    }
}


shared_ptr<Component> Group::check_get_component(weak_ptr<Component> component_ptr)
{
    shared_ptr<Component> sp = component_ptr.lock();
    if (!sp)
        children.erase(sp->get_name());
    return sp;
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

