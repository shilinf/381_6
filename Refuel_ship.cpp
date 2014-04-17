#include "Refuel_ship.h"
#include "Utility.h"
#include "Island.h"
#include "Model.h"
#include <iostream>
#include <cassert>
#include <set>

using std::cout; using std::endl;
using std::shared_ptr;
using std::set;

void Refuel_ship::update()
{
    Ship::update();
    if (!can_move()) {
        if (refuel_ship_state != NO_REFUEL_PATH) {
            clear_path();
            cout << get_name() << " now has no refuel path" << endl;
        }
        return;
    }
    switch(refuel_ship_state) {
        case NO_REFUEL_PATH:
            break;
        case LOADING:
        {
            refuel();
            double depot_needed = depot_capacity - depot;
            if (depot_needed < 0.005) {
                depot = depot_capacity;
                Ship::set_destination_position_and_speed(terminus, get_maximum_speed());
                refuel_ship_state = MOVING_TO_TERMINUS;
            }
            else {
                depot += load_destination->provide_fuel(depot_needed);
                cout << "Depot of " << get_name() << " now has " << depot 
                    << " of fuel" << endl;
            }
            break;
        }
        case MOVING_TO_TERMINUS:
            if (!find_dead_ship() && !is_moving())
                moving_to_loading();
            break;
        case MOVING_TO_LOADING:
            if (!find_dead_ship() && !is_moving() && can_dock(load_destination)) {
                dock(load_destination);
                refuel_ship_state = LOADING;
            }
            break;
        case MOVING_TO_SHIP:
        {
            shared_ptr<Ship> sp = get_target();
            if (!sp) {
                cout << "the target of " << get_name() <<
                " has sunk, return to island" << endl;
                moving_to_loading();
            } else {
                if (!is_moving()) {
                    refuel_ship_state = REFUEL_SHIP;
                }
            }
            break;
        }
        case REFUEL_SHIP:
            if (!is_moving()) {
                shared_ptr<Ship> sp = get_target();
                if (!sp)
                    cout << "the target of " << get_name() <<
                    " has sunk, return to island" << endl;
                else {
                    cout << get_name() << " refuels target" << endl;
                    double refuel_amount = sp->receive_fuel(depot, shared_from_this());
                    depot -= refuel_amount;
                }
                moving_to_loading();
            }
    }
}

void Refuel_ship::describe() const
{
    cout << "\nRefuel_ship ";
    Ship::describe();
    cout << "Depot: " << depot << " tons";
    switch (refuel_ship_state) {
        case NO_REFUEL_PATH:
            cout << ", no refuel path";
            break;
        case LOADING:
            cout << ", loading";
            break;
        case MOVING_TO_TERMINUS:
            cout << ", moving to terminus";
            break;
        case MOVING_TO_LOADING:
            cout << ", moving to loading destination";
            break;
        case MOVING_TO_SHIP:
        {
            shared_ptr<Ship> sp = get_target();
            if (sp)
                cout << ", moving to dead ship " << get_target()->get_name();
            else
                cout << ", target is sunk";
            break;
        }
        case REFUEL_SHIP:
        {
            shared_ptr<Ship> sp = get_target();
            if (sp)
                cout << ", refueling dead ship " << get_target()->get_name();
            else
                cout << ", target is sunk";
            break;
        }
        default:
            assert(false);
            break;
    }
    cout << endl;
}


void Refuel_ship::set_destination_position_and_speed(Point destination, double speed)
{
    check_no_path();
    Ship::set_destination_position_and_speed(destination, speed);
}

void Refuel_ship::set_course_and_speed(double course, double speed)
{
    check_no_path();
    Ship::set_course_and_speed(course, speed);
}

void Refuel_ship::set_load_destination(shared_ptr<Island> destination)
{
    check_no_path();
    load_destination = destination;
    set_terminus(get_location());
    cout << get_name() << " will refill depot at " << destination->get_name() << endl;
    start_cycle();
}
    
void Refuel_ship::set_terminus(Point position)
{
    terminus = position;
}

void Refuel_ship::stop()
{
    Ship::stop();
    clear_path();
    cout << get_name() << " now has no path" << endl; 
    
}

void Refuel_ship::check_no_path()
{
    if (refuel_ship_state != NO_REFUEL_PATH)
        throw Error("Refuel_ship has refuel path!");
}

void Refuel_ship::clear_path()
{
    load_destination.reset();
    refuel_ship_state = NO_REFUEL_PATH;
}

void Refuel_ship::start_cycle()
{
    if (is_docked() && get_docked_Island() == load_destination)
        refuel_ship_state = LOADING;
    else if (can_dock(load_destination)) {
        dock(load_destination);
        refuel_ship_state = LOADING;
    }
    else {
        Ship::set_destination_position_and_speed(load_destination->get_location(),
                                                    get_maximum_speed());
        refuel_ship_state = MOVING_TO_LOADING;
    }
}

bool Refuel_ship::find_dead_ship()
{
    set<shared_ptr<Ship>, Sim_object_comp> all_ships = Model::get_instance().get_all_ships();
    for (auto& ship_ptr : all_ships) {
        if (ship_ptr->get_owner_ptr() == get_owner_ptr()) {
            double distance = cartesian_distance(get_location(), ship_ptr->get_location());
            if (distance < perception && !ship_ptr->can_move() && depot >= 0.005) {
                target_ptr = ship_ptr;
                Ship::set_destination_position_and_speed(get_target()->get_location(), 
                                                         get_maximum_speed());
                refuel_ship_state = MOVING_TO_SHIP;
                return true;
            }
        }
    }
    return false;
}

void Refuel_ship::moving_to_loading()
{
    Ship::set_destination_position_and_speed(load_destination->get_location(),
                                             get_maximum_speed());
    refuel_ship_state = MOVING_TO_LOADING;
}

shared_ptr<Ship> Refuel_ship::get_target() const
{
    return target_ptr.lock();
}
