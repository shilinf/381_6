#ifndef DESTINATION_VIEW_H
#define DESTINATION_VIEW_H

#include "View.h"
#include "Geometry.h"
#include <string>
#include <map>

class Destination_view : public View {
public:
    void update_location(const std::string& name, Point location) override;
    
    void update_speed(const std::string& name, double speed) override;
    
	// Remove the ship; no error if the name is not present.
	void update_remove(const std::string& name) override;
	
	void update_destination(const std::string& name, Point destination) override;
	
	// draw the destination view
	void draw() override;
	
	// Discard the saved information - drawing will show only a empty pattern
	void clear() override;

private:
    struct Destination_location {
        Point destination;
        Point location;
        bool is_ship {false};
    };

    std::map<std::string, Destination_location> destination_location_container;
};

#endif
