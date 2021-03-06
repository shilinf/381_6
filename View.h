#ifndef VIEW_H
#define VIEW_H

/* This class provides the interface for all of view objects. */

#include "Geometry.h"
#include <string>

class View {
public:
    virtual ~View() {}
    
	virtual void update_location(const std::string& name, Point location) {}
    
    virtual void update_fuel(const std::string& name, double fuel) {}
    
    virtual void update_course(const std::string& name, double course) {}
    
    virtual void update_speed(const std::string& name, double speed) {}
    
    virtual void update_destination(const std::string& name, Point destination) {}
    
	// Remove the ship; no error if the name is not present.
	virtual void update_remove(const std::string& name) {};
    
	// prints out the current view
	virtual void draw() = 0;
	
	// Discard the saved information - drawing will show only a empty pattern
	virtual void clear() = 0;
};

#endif
