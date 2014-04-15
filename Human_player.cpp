#include "Human_player.h"
#include "Model.h"
#include "View.h"
#include "Map_view.h"
#include "Sailing_view.h"
#include "Bridge_view.h"
#include "Destination_view.h"
#include "Ship.h"
#include "Group.h"
#include "Island.h"
#include "Geometry.h"
#include "Ship_factory.h"
#include "Utility.h"
#include <iostream>
#include <utility>
#include <algorithm>
#include <functional>

using std::string;
using std::cout; using std::cin; using std::endl;
using std::map;
using std::shared_ptr;
using std::for_each; using std::find_if;
using std::mem_fn;

Human_player::Human_player(const string& name_) : Player(name_)
{
    commands_map["open_map_view"] = &Human_player::open_map_view;
    commands_map["close_map_view"] = &Human_player::close_map_view;
    commands_map["open_sailing_view"] = &Human_player::open_sailing_view;
    commands_map["close_sailing_view"] = &Human_player::close_sailing_view;
    commands_map["open_bridge_view"] = &Human_player::open_bridge_view;
    commands_map["close_bridge_view"] = &Human_player::close_bridge_view;
    commands_map["open_destination_view"] = &Human_player::open_destination_view;
    commands_map["close_destination_view"] = &Human_player::close_destination_view;
    
    commands_map["default"] = &Human_player::restore_default_map;
    commands_map["size"] = &Human_player::set_map_size;
    commands_map["zoom"] = &Human_player::set_map_scale;
    commands_map["pan"] = &Human_player::set_map_origin;
    commands_map["show"] = &Human_player::draw_map;
    commands_map["status"] = &Human_player::show_object_status;
    //commands_map["go"] = &Human_player::update_all_objects;
    commands_map["create"] = &Human_player::create_new_ship;
    commands_map["create_group"] = &Human_player::create_new_group;
    
    //ssx
    commands_map["set_terminus"] = &Human_player::set_component_terminus;
    commands_map["course"] = &Human_player::set_component_course;
    commands_map["position"] = &Human_player::set_component_to_position;
    commands_map["destination"] = &Human_player::set_component_destination_island;
    commands_map["load_at"] = &Human_player::set_component_load_island;
    commands_map["unload_at"] = &Human_player::set_component_unload_island;
    commands_map["dock_at"] = &Human_player::set_component_dock_island;
    commands_map["attack"] = &Human_player::set_component_attack_target;
    commands_map["refuel"] = &Human_player::set_component_refuel;
    commands_map["stop"] = &Human_player::set_component_stop;
    commands_map["stop_attack"] = &Human_player::set_component_stop_attack;
    commands_map["remove"] = &Human_player::remove_group_component;
    commands_map["add"] = &Human_player::add_group_component;
    commands_map["disband"] = &Human_player::disband_group;
}

void Human_player::init()
{
    
}

bool Human_player::run()
{
    string first_word, command;
    while (true) {
        cout << "\nTime " << Model::get_instance().get_time() << ": Enter command: ";
        cin >> first_word;
        if (first_word == "quit") {
            quit();
            return false;
        }
        else if(first_word == "go") {
            update_all_objects();
            return true;
        }
        try {
            if (Model::get_instance().is_component_present(first_word)) {
                // TO CHANGE: test presence and ownership
                target_component = Model::get_instance().get_component_ptr(first_word);
                cin >> command;
            }
            else
                command = first_word;
            auto cfp = commands_map[command];
            if (cfp)
                (this->*cfp)();
            else {
                commands_map.erase(command);
                cout << "Unrecognized command!" << endl;
                discard_input_remainder();
            }
        } catch (Error& error) {
            cout << error.what() << endl;
            discard_input_remainder();
        } catch (...) {
            cout << "Unknown exception caught!" << endl;
            return false;
        }
        target_component.reset();
    }
}

void Human_player::open_map_view()
{
    if (map_view_ptr)
        throw Error("Map view is already open!");
    map_view_ptr.reset(new Map_view);
    draw_view_order.push_back(map_view_ptr);
    Model::get_instance().attach(map_view_ptr);
}

void Human_player::close_map_view()
{
    check_map_view_exist();
    Model::get_instance().detach(map_view_ptr);
    remove_view(map_view_ptr);
    map_view_ptr.reset();
}

void Human_player::open_sailing_view()
{
    if (sailing_view_ptr)
        throw Error("Sailing data view is already open!");
    sailing_view_ptr.reset(new Sailing_view);
    draw_view_order.push_back(sailing_view_ptr);
    Model::get_instance().attach(sailing_view_ptr);
}

void Human_player::close_sailing_view()
{
    if (!sailing_view_ptr)
        throw Error("Sailing data view is not open!");
    Model::get_instance().detach(sailing_view_ptr);
    remove_view(sailing_view_ptr);
    sailing_view_ptr.reset();
}

void Human_player::open_bridge_view()
{
    string ship_name = read_string();
    if (!Model::get_instance().is_ship_present(ship_name))
        throw Error("Ship not found!");
    if (bridge_view_container.find(ship_name) != bridge_view_container.end())
        throw Error("Bridge view is already open for that ship!");
    shared_ptr<Bridge_view> new_bridge_view(new Bridge_view(ship_name));
    bridge_view_container[ship_name] = new_bridge_view;
    draw_view_order.push_back(new_bridge_view);
    Model::get_instance().attach(new_bridge_view);
}

void Human_player::close_bridge_view()
{
    string ship_name = read_string();
    auto bridge_view_it = bridge_view_container.find(ship_name);
    if (bridge_view_it == bridge_view_container.end())
    	throw Error("Bridge view for that ship is not open!");
    Model::get_instance().detach(bridge_view_it->second);
    remove_view(bridge_view_it->second);
    bridge_view_container.erase(bridge_view_it);
}

void Human_player::open_destination_view() {
    if (destination_view_ptr) {
        throw Error("Destination view is already open!");
    }
    destination_view_ptr.reset(new Destination_view);
    draw_view_order.push_back(destination_view_ptr);
    Model::get_instance().attach(destination_view_ptr);
}

void Human_player::close_destination_view() {
    if (!destination_view_ptr) {
        throw Error("Destination view is not open!");
    }
    remove_view(destination_view_ptr);
    destination_view_ptr.reset();
}

void Human_player::restore_default_map()
{
    check_map_view_exist();
    map_view_ptr->set_defaults();
}

void Human_player::set_map_size()
{
    check_map_view_exist();
    int size;
    if (!(cin >> size))
        throw Error("Expected an integer!");
    map_view_ptr->set_size(size);
}

void Human_player::set_map_scale()
{
    check_map_view_exist();
    double scale = read_double();
    map_view_ptr->set_scale(scale);
}

void Human_player::set_map_origin()
{
    check_map_view_exist();
    map_view_ptr->set_origin(read_point());
}

// draw all the exist maps
void Human_player::draw_map()
{
    for_each(draw_view_order.begin(), draw_view_order.end(), mem_fn(&View::draw));
}

void Human_player::check_map_view_exist()
{
    if (!map_view_ptr)
        throw Error("Map view is not open!");
}

void Human_player::show_object_status()
{
    Model::get_instance().describe();
}

void Human_player::update_all_objects()
{
    Model::get_instance().update();
}

void Human_player::create_new_ship()
{
    string name = read_string();
    if (name.length() < 2)
        throw Error("Name is too short!");
    if (Model::get_instance().is_name_in_use(name))
        throw Error("Name is already in use!");
    string ship_type = read_string();
    shared_ptr<Ship> new_ship = create_ship(name, ship_type, read_point());
    Model::get_instance().add_component(new_ship);
    Model::get_instance().add_ship(new_ship);
}

void Human_player::create_new_group()
{
    // considering use a function here !!!!!!!!!!!!!!!!
    string name = read_string();
    if (name.length() < 2)
        throw Error("Name is too short!");
    if (Model::get_instance().is_name_in_use(name))
        throw Error("Name is already in use!");
    shared_ptr<Component> new_component(new Group(name));
    Model::get_instance().add_component(new_component);
}

void Human_player::set_component_course()
{
    double course = read_double();
    double speed = read_check_speed();
    if (course < 0.0 || course >= 360.0)
        throw Error("Invalid heading entered!");
    target_component->set_course_and_speed(course, speed);
}

void Human_player::set_component_to_position()
{
    Point position = read_point();
    double speed = read_check_speed();
    target_component->set_destination_position_and_speed(position, speed);
}

void Human_player::set_component_destination_island()
{
    Point island_location = read_get_island()->get_location();
    target_component->set_destination_position_and_speed(island_location, read_check_speed());
}

void Human_player::set_component_load_island()
{
    target_component->set_load_destination(read_get_island());
}

void Human_player::set_component_unload_island()
{
    target_component->set_unload_destination(read_get_island());
}

void Human_player::set_component_dock_island()
{
    target_component->dock(read_get_island());
}

void Human_player::set_component_attack_target()
{
    string ship_name = read_string();
    shared_ptr<Ship> attack_ship = Model::get_instance().get_ship_ptr(ship_name);
    target_component->attack(attack_ship);
}

void Human_player::set_component_refuel()
{
    target_component->refuel();
}

void Human_player::set_component_stop()
{
    target_component->stop();
}

void Human_player::set_component_stop_attack()
{
    target_component->stop_attack();
}

// if remove_component is not in the group, won't throw exception
void Human_player::remove_group_component()
{
    string remove_component_name = read_string();
    shared_ptr<Component> remove_component_ptr = Model::get_instance().get_component_ptr(remove_component_name);
    target_component->remove_component(remove_component_ptr);
    Model::get_instance().remove_group_member(remove_component_name);
}

void Human_player::add_group_component()
{
    string new_component_name = read_string();
    if (target_component->get_name() == new_component_name)
        throw Error("Cannot add itself!");
    shared_ptr<Component> new_component_ptr = Model::get_instance().get_component_ptr(new_component_name);
    Model::get_instance().add_group_member(new_component_name);
    target_component->add_component(new_component_ptr);
}

void Human_player::disband_group()
{
    target_component->disband();
    Model::get_instance().remove_component(target_component);
}

void Human_player::set_component_terminus()
{
    target_component->set_terminus(read_point());
}

void Human_player::quit()
{
    cout << "Done" << endl;
}

double Human_player::read_check_speed()
{
    double speed = read_double();
    if (speed < 0.0)
        throw Error("Negative speed entered!");
    return speed;
}



// Read to new line
void Human_player::discard_input_remainder()
{
    cin.clear();
    while (cin.get() != '\n')
        ;
}

Point Human_player::read_point()
{
    double x = read_double();
    double y = read_double();
    return Point(x, y);
}


double Human_player::read_double()
{
    double temp;
    if (!(cin >> temp))
        throw Error("Expected a double!");
    return temp;
}

string Human_player::read_string()
{
    string read_string;
    cin>>read_string;
    return read_string;
}

shared_ptr<Island> Human_player::read_get_island()
{
    string island_name = read_string();
    return Model::get_instance().get_island_ptr(island_name);
}

void Human_player::remove_view(std::shared_ptr<View> view)
{
    auto view_it = find_if(draw_view_order.begin(), draw_view_order.end(),
                           [&view](shared_ptr<View> view_ptr){return view_ptr == view;});
    draw_view_order.erase(view_it);
}
