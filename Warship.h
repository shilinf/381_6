#ifndef WARSHIP_H
#define WARSHIP_H

/* A Warship is a ship with firepower and range member variables, and some services for
protected classes to manage many of the details of warship behavior. This is an
abstract base class, so concrete classes derived from Warship must be declared.
*/

#include "Ship.h"
#include <string>
#include <memory>

class Player;
struct Point;

class Warship : public Ship {
public:
	Warship(const std::string& name_, Point position_, double fuel_capacity_,
		double maximum_speed_, double fuel_consumption_, int resistance_,
        int firepower_, double maximum_range_, std::shared_ptr<Player> owner_ptr_) :
        Ship(name_, position_, fuel_capacity_, maximum_speed_, fuel_consumption_, 
        resistance_, owner_ptr_), firepower(firepower_), maximum_range(maximum_range_), 
        attacking(false) {}
	
	virtual ~Warship() = 0;
	
	void update() override;

    void describe() const override;
	
    // perform warship-specific behavior
    // Warships will act on an attack and stop_attack command

	// will	throw Error("Cannot attack!") if not Afloat
	// will throw Error("Warship may not attack itself!")
    // if supplied target is the same as this Warship
	void attack(std::shared_ptr<Ship> target_ptr_) override;

	// will throw Error("Was not attacking!") if not Attacking
	void stop_attack() override;	

protected:
	// return true if this Warship is in the attacking state
	bool is_attacking() const;
	
	// fire at the current target
	void fire_at_target();
		
	// is the current target in range?
	bool target_in_range() const;

	// get the target
    std::shared_ptr<Ship> get_target() const;
    
private:
    int firepower;
    double maximum_range;
    bool attacking;
    std::weak_ptr<Ship> target_ptr;
};

#endif
