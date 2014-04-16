#ifndef SIM_OBJECT_H
#define SIM_OBJECT_H
/* This class provides the interface for all of simulation objects. It also stores the
object's name, owner_ptr and has pure virtual accessor functions for the object's position
and other information. */

#include <string>
#include <memory>

class Player;
struct Point;

class Sim_object {
public:
	Sim_object(const std::string& name_, std::shared_ptr<Player> owner_ptr_) : name(name_), owner_ptr(owner_ptr_) {}

    virtual ~Sim_object() {}
	
	const std::string& get_name() const
		{return name;}
    
    const std::shared_ptr<Player> get_owner_ptr() const
        {return owner_ptr;}
    
    void reset_owner_ptr()
        {owner_ptr.reset();}
    
	// ask model to notify views of current state
    virtual void broadcast_current_state() {}

	/* Interface for derived classes */
	virtual void describe() const = 0;
	virtual void update() = 0;
    
    // fat interface
    // will always throw Error("Cannot get location!")
    virtual Point get_location() const;
	
private:
	std::string name;
    std::shared_ptr<Player> owner_ptr;
};


#endif

