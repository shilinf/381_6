#ifndef SIM_OBJECT_H
#define SIM_OBJECT_H
/* This class provides the interface for all of simulation objects. It also stores the
object's name, and has pure virtual accessor functions for the object's position
and other information. */

#include <string>
#include <memory>

class Player;
struct Point;

class Sim_object {
public:
    // *** define the constructor in Sim_object.cpp to output the supplied message
	Sim_object(const std::string& name_, std::shared_ptr<Player> owner_ptr_) : name(name_), owner_ptr(owner_ptr_) {}

    // *** define the destructor in Sim_object.cpp to output the supplied message
    virtual ~Sim_object() {}
	
	const std::string& get_name() const
		{return name;}
    
    std::shared_ptr<Player> get_owner_ptr()
        {return owner_ptr;}
    
	// ask model to notify views of current state
    virtual void broadcast_current_state() {}

	/* Interface for derived classes */
	// *** declare the following as pure virtual functions 
	virtual Point get_location() const;
	virtual void describe() const = 0;
	virtual void update() = 0;
	
private:
	std::string name;
    std::shared_ptr<Player> owner_ptr;
};


#endif

