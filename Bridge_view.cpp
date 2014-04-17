#include "Bridge_view.h"
#include "Navigation.h"
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>

using std::string;
using std::cout; using std::endl;
using std::vector;
using std::string;
using std::setw;

void Bridge_view::update_location(const string& name, Point location)
{
    points[name] = location;
}

void Bridge_view::update_course(const string& name, double course)
{
    if (ownship_name == name)
        ownship_course = course;
}

void Bridge_view::update_remove(const string& name)
{
    if (name == ownship_name)
        sunk = true;
    else
        points.erase(name);
}

void Bridge_view::draw()
{
    vector< vector<string> > output;
    Point own_location = points[ownship_name];
    if (sunk) {
        cout << "Bridge view from " << ownship_name << " sunk at " <<
        own_location << endl;
        output = vector< vector<string> >(3, vector<string>(19, "w-"));
    }
    else {
        cout << "Bridge view from " << ownship_name <<  " position "
        << own_location << " heading " << ownship_course << endl;
        output = vector< vector<string> >(3, vector<string>(19, ". "));
        for (auto& map_pair : points) {
            Compass_position relative_position(own_location, map_pair.second);
            if (relative_position.range >= 0.005 && relative_position.range <= 20.) {
                int x;
                if (compute_subscribt(relative_position.bearing, x)) {
                    if (output[2][x] == ". ")
                        output[2][x] = map_pair.first.substr(0, 2);
                    else
                        output[2][x] = "**";
                }
            }
        }
    }
    for (int i = 0 ; i < 3; i++) {
        cout << setw(4) << "" << ' ';
        for (int j = 0; j < 19; j++)
            cout << output[i][j];
        cout << endl;
    }
    for (int i = 0; i <= 6 ; i++) {
        cout << "  " << setw(4) << -90 + 3 * 10 * i;
    }
    cout << endl;
}

void Bridge_view::clear()
{
    points.clear();
}

bool Bridge_view::compute_subscribt(double bearing, int &x)
{
    double bridge_view_angle = bearing - ownship_course;
    if (bridge_view_angle < -180.)
        bridge_view_angle += 360.;
    else if (bridge_view_angle > 180.)
        bridge_view_angle -= 360.;
    double delta_x = (bridge_view_angle + 90.) / 10.0;
	x = int(floor(delta_x));
    return (x >= 0 && x <= 18);
}
