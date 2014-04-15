#ifndef REFUEL_SHIP_H
#define REFUEL_SHIP_H

#include "Ship.h"
#include <memory>
#include <string>

/*
A Refuel_ship is a ship with a large cargo capacity for fuel.
It can be told an Island to load fuel at, and an arbitrary terminus to travel back and forth.
At loading destination, it will first refuel then wati until its cargo hold is full, then it
will go to the arbitrary point. 
If on the course between the two points, there is a DEAD_IN_WATER ship, it will go to that place
and refuel the DEAD_IN_WATER ship, once refueled the ship, it directly goes back to the island
and return the loop. The DEAD_IN_WATER ship will change the state to stop.

Initial values:
fuel capcity and initial amount 400 tons, maximum speed 10., fuel consumption 2.tons/nm,
resistance 0, cargo capacity 1000 tons, initial cargo is 0 tons. 
The prceive distance is 20nm
The terminus is the original place of the ship.
*/

class Island;

class Refuel_ship : public Ship {
public:
    // initialize
    Refuel_ship(const std::string& name_, Point position_, std::shared_ptr<Player> owner_ptr_) :
        Ship(name_, position_, 400., 10., 2., 0, owner_ptr_), depot_capacity(2000.), depot(0.),
        refuel_ship_state(NO_REFUEL_PATH), load_destination(nullptr), terminus(position_),  
        perception(20.) {}

    // This class overrides ship functions.
    // If the Refuel_ship has a load_destination, throw Error("Refuel_ship has refuel path!"); otherwise simply class Ship function.
    void set_destination_position_and_speed(Point destination, double speed) override;
    
    void set_course_and_speed(double course, double speed) override;

    // Set the load_destination
    // If load_destination is already set, throw Error("Refuel_ship has load destination!").
    // Set it and then start the cycle
    void set_load_destination(std::shared_ptr<Island>) override;

    // Set the terminus
    // The new terminus will be available in the next round
    void set_terminus(Point position) override;

    // when told to stop, clear the load destination and set terminus to current location
    void stop() override;
    
    void update() override;
    
    void describe() const override;


private:
    enum Refuel_ship_state_e {NO_REFUEL_PATH, LOADING, MOVING_TO_TERMINUS, MOVING_TO_LOADING,
                                MOVING_TO_SHIP, REFUEL_SHIP};
    double depot_capacity;
    double depot;
    Refuel_ship_state_e refuel_ship_state;
    std::shared_ptr<Island>load_destination;
    Point terminus;
    double perception;
    std::weak_ptr<Ship> target_ptr;

    void check_no_path();
    void clear_path();
    void start_cycle();
    bool find_dead_ship();
    void moving_to_loading();
    std::shared_ptr<Ship> get_target() const;
};
#endif
