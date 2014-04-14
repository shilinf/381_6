#ifndef COMPONENT_H
#define COMPONENT_H

#include "Sim_object.h"
#include <memory>
#include <set>

class Island;
class Ship;

class Component : public Sim_object {
public:
    Component(const std::string& name_) : Sim_object(name_) {}
    
	/*** Command functions ***/
	// Start moving to a destination position at a speed
    // may throw Error("Ship cannot move!")
    // may throw Error("Ship cannot go that fast!")
	virtual void set_destination_position_and_speed(Point destination_position, double speed) = 0;
	// Start moving on a course and speed
    // may throw Error("Ship cannot move!")
    // may throw Error("Ship cannot go that fast!");
	virtual void set_course_and_speed(double course, double speed) = 0;
	// Stop moving
    // may throw Error("Ship cannot move!");
	virtual void stop() = 0;
	// dock at an Island - set our position = Island's position, go into Docked state
    // may throw Error("Can't dock!");
	virtual void dock(std::shared_ptr<Island> island_ptr) = 0;
	// Refuel - must already be docked at an island; fill takes as much as possible
    // may throw Error("Must be docked!");
	virtual void refuel() = 0;
    
    
// pure virtual functions
    
	/*** Fat interface command functions ***/
	// These functions throw an Error exception for this class
    // will always throw Error("Cannot load at a destination!");
	virtual void set_load_destination(std::shared_ptr<Island>) = 0;
    // will always throw Error("Cannot unload at a destination!");
	virtual void set_unload_destination(std::shared_ptr<Island>) = 0;
    // will always throw Error("Cannot attack!");
	virtual void attack(std::shared_ptr<Ship> in_target_ptr) = 0;
    // will always throw Error("Cannot attack!");
	virtual void stop_attack() = 0;
    
    virtual void set_terminus(Point position) = 0;
    
    // interactions with other objects
	// receive a hit from an attacker
    
    virtual void add_component(std::shared_ptr<Component> component_ptr);
    
    virtual void remove_component(std::shared_ptr<Component> component_ptr);
    
    //virtual void get_all_contained_component(std::set<std::shared_ptr<Component> >& all_components) {}
};

#endif
