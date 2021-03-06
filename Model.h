#ifndef MODEL_H
#define MODEL_H

/*
Model is part of a simplified Model-View-Controller pattern.
Model keeps track of the Sim_objects in our little world. It knows 
how many Islands and Ships there are, but it does not
know about any of their derived classes, nor which Ships are of what kind of Ship. 
It has facilities for looking up objects by name, and removing Ships.
Finally, it keeps the system's time.

Human Player tells Model what to do; Model in turn tells the objects what do, and
when asked to do so by an object, tells all the Views whenever anything changes 
that might be relevant. Model also provides facilities for looking up objects 
given their name.
*/

#include "Utility.h"
#include <string>
#include <map>
#include <set>
#include <memory>

class Sim_object;
class Island;
class Component;
class Ship;
class View;
struct Point;

class Model {
public:
    static Model& get_instance();
    
	// return the current time
	int get_time() {return time;}
	
	// is name already in use for either ship or island?
    // either the identical name, or identical in first two characters counts as in-use
	bool is_name_in_use(const std::string& name) const;

	// is there such an island?
	bool is_island_present(const std::string& name) const;
	// add a new island to the lists
	void add_island(std::shared_ptr<Island>);
	// will throw Error("Island not found!") if no island of that name
	std::shared_ptr<Island> get_island_ptr(const std::string& name) const;

	// is there such an ship?
	bool is_ship_present(const std::string& name) const;
	// add a new ship to the list, and update the view
	void add_ship(std::shared_ptr<Ship>);
	// will throw Error("Ship not found!") if no ship of that name
	std::shared_ptr<Ship> get_ship_ptr(const std::string& name) const;
    
    // is there such an component?
	bool is_component_present(const std::string& name) const;
	// add a new component to the list, and update the view
	void add_component(std::shared_ptr<Component>);
	// will throw Error("Component not found!") if no component of that name
	std::shared_ptr<Component> get_component_ptr(const std::string& name) const;
    
	// tell all objects to describe themselves
	void describe() const;
	// increment the time, and tell all objects to update themselves
	void update();
	   
	/* View services */
	// Attaching a View adds it to the container and causes it to be updated
    // with all current objects'location (or other state information.
	void attach(std::shared_ptr<View>);
	// Detach the View by discarding the supplied pointer from the container of Views
    // - no updates sent to it thereafter.
	void detach(std::shared_ptr<View>);
    
    // notify the views about an object's location
	void notify_location(const std::string& name, Point location);
    
    // notify the views about an object's fuel
    void notify_fuel(const std::string& name, double fuel);
    
    // notify the views about an object's course
    void notify_course(const std::string& name, double course);
    
    // notify the views about an object's speed
    void notify_speed(const std::string& name, double speed);
    
	// notify the views that an object is now gone
	void notify_gone(const std::string& name);
	
	// notify the views about a ship's destination
	void notify_destination(const std::string& name, Point destination);
    
    // remove a component from the simulated world.
    // No error if the component is not a ship or the component is
    // not in components_not_in_group container
    void remove_component(std::shared_ptr<Component> ship_ptr);
    
    std::set<std::shared_ptr<Island>, Sim_object_comp> get_all_islands() const;

    std::set<std::shared_ptr<Ship>, Sim_object_comp> get_all_ships() const;
    
    std::set<std::shared_ptr<Component>, Sim_object_comp> get_all_components() const;
    
private:
	int time;		// the simulated time
    std::map<std::string, std::shared_ptr<Sim_object>> object_container;
    std::map<std::string, std::shared_ptr<Island>> island_container;
    std::map<std::string, std::shared_ptr<Component>> component_container;
    std::map<std::string, std::shared_ptr<Ship>> ship_container;
    std::set<std::shared_ptr<View>> view_container;
    
	Model() : time(0) {}
    
	// disallow copy/move construction or assignment
    Model(const Model &) = delete;
    Model(Model &&) = delete;
    Model &operator= (const Model &) = delete;
    Model &operator= (Model &&) = delete;
};

#endif
