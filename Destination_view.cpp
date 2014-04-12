#include "Destination_view.h"
#include "Model.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using std::string;
using std::cout; using std::endl;
using std::setw;
using std::ostringstream;
using std::ios;

void Destination_view::update_location(const string& name, Point location)
{
    if (Model::get_instance().is_ship_present(name)) {
        destination_location_container[name].location = location;
    }   
}

// Remove the ship if its speed is 0
void Destination_view::update_speed(const string& name, double speed)
{
    if (destination_location_container.find(name) != destination_location_container.end()) {
        if (speed == 0.) {
            destination_location_container.erase(name);
        }
    }
}

// Remove the ship; no error if the name is not present.
void Destination_view::update_remove(const string& name)
{
    destination_location_container.erase(name);
}

void Destination_view::update_destination(const string& name, Point destination)
{
    destination_location_container[name].destination = destination;
}

// draw the destination view
void Destination_view::draw()
{
    cout << "----- Destination Data -----" << endl;
    cout << setw(10) << "Ship" << setw(15) << "Destination" << setw(10) 
        << "Distance" << endl;
        
    ostringstream osstream;
    osstream.setf(ios::fixed, ios::floatfield);
    osstream.precision(2);
    
    for (auto& entry : destination_location_container) {
        double distance = cartesian_distance(entry.second.destination, 
            entry.second.location);
        osstream.str("");
        osstream << '(' << entry.second.destination.x << ", " 
            << entry.second.destination.y << ')';
        cout << setw(10) << entry.first << setw(15) << osstream.str() << setw(10) 
            << distance << endl;
    }
}

// Discard the saved information - drawing will show only a empty pattern
void Destination_view::clear()
{
    destination_location_container.clear();
}
