#ifndef SAILING_VIEW_H
#define SAILING_VIEW_H

#include "View.h"
#include "Navigation.h"
#include "Geometry.h"
#include <map>
#include <string>

class Sailing_view : public View {
public:
    void update_fuel(const std::string& name, double fuel) override;
    
    void update_course(const std::string& name, double course) override;
    
    void update_speed(const std::string& name, double speed) override;
    
    // Remove the ship; no error if the name is not present.
    void update_remove(const std::string& name) override;
    
	// prints out the current map
    void draw() override;
	
	// Discard the saved information - drawing will show only a empty pattern
    void clear() override;
    
private:
    struct Fuel_course_speed
    {
        Course_speed cs;
        double fuel;
        Fuel_course_speed(Course_speed cs_ = Course_speed(), double fuel_ = 0.) :
        cs(cs_), fuel(fuel_){}
    };
    std::map<std::string, Fuel_course_speed> ships_info;
};


#endif
