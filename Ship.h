#ifndef SHIP_H
#define SHIP_H

/* A Ship has a name, initial position, amount of fuel, and parameters 
that govern its movement. It can be commanded to move to either a position or 
follow a course, or stop, dock at or refuel at an Island. It consumes fuel while
moving, and becomes immobile if it runs out of fuel. It inherits the Component 
interface to the rest of the system, and the Track_base class provides the basic
movement functionality, with the unit of time corresponding to 1.0 for one "tick"
- an hour of simulated time.

The update function updates the position and/or state of the ship.
The describe function outputs information about the ship state.
Accessors make the ship state available to either the public or to derived classes.
This is a "fat interface" for the capabilities of derived types of Ships. These
functions are implemented in this class to throw an Error exception.
*/

#include "Component.h"
#include "Geometry.h"
#include "Track_base.h"
#include <string>
#include <memory>

class Player;
class Island;

class Ship : public Component, public std::enable_shared_from_this<Ship> {
public:
	Ship(const std::string& name_, Point position_, double fuel_capacity_,
        double maximum_speed_, double fuel_consumption_, int resistance_, 
        std::shared_ptr<Player> owner_ptr_) :
        Component(name_, owner_ptr_), fuel_capacity(fuel_capacity_), 
        fuel(fuel_capacity_), maximum_speed(maximum_speed_), 
        fuel_consumption(fuel_consumption_),
        resistance(resistance_), ship_state(STOPPED), track(position_) {}
	
	virtual ~Ship() = 0;
	
	/* Readers */
	// return the current position
	Point get_location() const override {return track.get_position();}
	
	// Return true if ship can move (it is not dead in the water or sunk);
	bool can_move() const;
	
	// Return true if ship is moving;
	bool is_moving() const;

	// Return true if ship is docked; 
	bool is_docked() const;
	
	// Return true if ship is afloat, false if not
	bool is_afloat() const;
    
	// Return true if the ship is Stopped and the distance to the supplied island
	// is less than or equal to 0.1 nm
	bool can_dock(std::shared_ptr<Island> island_ptr) const;
	
	/*** Interface to derived classes ***/
    // Update the state of the Ship
    void update() override;
    // output a description of current state to cout
    void describe() const override;

    void broadcast_current_state() override;

	/*** Command functions ***/
	// Start moving to a destination position at a speed
     // may throw Error("Ship cannot move!")
     // may throw Error("Ship cannot go that fast!")
    void set_destination_position_and_speed(Point destination_position, 
        double speed) override;
	// Start moving on a course and speed
     // may throw Error("Ship cannot move!")
     // may throw Error("Ship cannot go that fast!");
    void set_course_and_speed(double course, double speed) override;
	// Stop moving
     // may throw Error("Ship cannot move!");
    void stop() override;
	// dock at an Island - set our position = Island's position, go into Docked state
     // may throw Error("Can't dock!");
    void dock(std::shared_ptr<Island> island_ptr) override;
	// Refuel - must already be docked at an island; fill takes as much as possible
     // may throw Error("Must be docked!");
    void refuel() override;

	/*** Fat interface command functions ***/
	// These functions throw an Error exception for this class
    // will always throw Error("Cannot load at a destination!");
    void set_load_destination(std::shared_ptr<Island>) override;
    // will always throw Error("Cannot unload at a destination!");
    void set_unload_destination(std::shared_ptr<Island>) override;
    // will always throw Error("Cannot attack!");
    void attack(std::shared_ptr<Ship> in_target_ptr) override;
    // will always throw Error("Cannot attack!");
	void stop_attack() override;
	// will always throw Error("Cannot set terminus!");
    void set_terminus(Point position) override;
	
	// interactions with other objects
	// receive a hit from an attacker
	virtual void receive_hit(int hit_force, std::shared_ptr<Ship> attacker_ptr);
	
	// receive fuel from a refuel_ship.
	// the argument is the refuel_ship and the available fuel in the depot
	// return the actual refuel amount
	virtual double receive_fuel(double available, std::shared_ptr<Ship> refuel_ship);
		
protected:
	double get_maximum_speed() const
        {return maximum_speed;}
	// return pointer to the Island currently docked at, or nullptr if not docked
	std::shared_ptr<Island> get_docked_Island() const;

private:
    enum Ship_state_e {MOVING_TO_POSITION, STOPPED, DEAD_IN_THE_WATER,
        MOVING_ON_COURSE, DOCKED, SUNK};
    double fuel_capacity;
	double fuel;						// Current amount of fuel
    double maximum_speed;
	double fuel_consumption;			// tons/nm required
    int resistance;
    Ship_state_e ship_state;
    Point destination;					// Current destination if any
    Track_base track;
    std::shared_ptr<Island>docked_at;

    void check_and_set_course_speed(double course, double speed);
    void notify_course_and_speed();
    // Updates position, fuel, and movement_state, assuming 1 time unit (1 hr)
    void calculate_movement();

	// disallow copy/move, construction or assignment
    Ship(const Ship&) = delete;
    Ship(Ship&&) = delete;
    Ship &operator= (const Ship&) = delete;
    Ship &operator= (Ship &&) = delete;
};

#endif

