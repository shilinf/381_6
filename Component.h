#ifndef COMPONENT_H
#define COMPONENT_H

#include "Sim_object.h"
#include <set>

class Island;
class Ship;

class Component : public Sim_object {
public:
    Component(const std::string& name_, std::shared_ptr<Player> owner_ptr_) : Sim_object(name_, owner_ptr_), is_contained(false) {}

    bool is_in_group()
        {return is_contained;}
    
    void added_to_group()
        {is_contained = true;}
    
    void removed_from_group()
        {is_contained = false;}
    
    /* Interface for derived classes */
	virtual void set_destination_position_and_speed(Point destination_position, double speed) = 0;

	virtual void set_course_and_speed(double course, double speed) = 0;

	virtual void stop() = 0;

	virtual void dock(std::shared_ptr<Island> island_ptr) = 0;

	virtual void refuel() = 0;

	virtual void set_load_destination(std::shared_ptr<Island>) = 0;

	virtual void set_unload_destination(std::shared_ptr<Island>) = 0;

	virtual void attack(std::shared_ptr<Ship> in_target_ptr) = 0;

	virtual void stop_attack() = 0;
    
    virtual void set_terminus(Point position) = 0;
    
    /* Fat interface functions */
    // will always throw Error("Cannot add component!")
    virtual void add_component(std::shared_ptr<Component> component_ptr);
    // will always throw Error("Cannot remove component!")
    virtual void remove_component(std::shared_ptr<Component> component_ptr);
    // will always throw Error("Cannot disband!")
    virtual void disband();
    // throw error if component_ptr's name is the same with this's name
    virtual void check_contain_component(std::shared_ptr<Component> component_ptr);
    
private:
    bool is_contained;
};

#endif
