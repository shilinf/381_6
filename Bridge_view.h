#ifndef BRIDGE_VIEW_H
#define BRIDGE_VIEW_H

#include "View.h"
#include "Navigation.h"
#include "Geometry.h"
#include <map>
#include <string>


class Bridge_view : public View {
public:
    Bridge_view(std::string ownship_name_) :
    ownship_name(ownship_name_), sunk(false) {}
    
    void update_course(const std::string& name, double course) override;
    
    void update_location(const std::string& name, Point location) override;
	
	// Remove the ship; no error if the name is not present.
    void update_remove(const std::string& name) override;
    
	// prints out the current map
    void draw() override;
	
	// Discard the saved information - drawing will show only a empty pattern
    void clear() override;
    
private:
    std::string ownship_name;
    double ownship_course;
    bool sunk;
    std::map<std::string, Point> points;
    
    bool compute_subscribt(double bearing, int &x);
};

#endif
