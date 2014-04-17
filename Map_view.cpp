#include "Map_view.h"
#include "Utility.h"
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>

using std::cout; using std::endl;
using std::vector;
using std::string;
using std::ios; using std::setw; using std::streamsize;

Map_view::Map_view()
{
    set_defaults();
}

void Map_view::update_location(const std::string& name, Point location)
{
    points[name] = location;
}

void Map_view::update_remove(const std::string& name)
{
    points.erase(name);
}

void Map_view::draw()
{
    class Cout_format_saver {
    public:
        Cout_format_saver() :
        old_flags(cout.flags()), old_precision(cout.precision()) {}
        ~Cout_format_saver() {
            cout.flags(old_flags);
            cout.precision(old_precision);
        }
    private:
        ios::fmtflags old_flags;
        streamsize old_precision;
    };
    
    cout << "Display size: " <<size << ", scale: " << scale << ", origin: " << origin << endl;
    vector< vector<string> > output(size, vector<string>(size, ". "));
    bool exist_out_of_map = false;
    for (auto& map_pair : points) {
        int x, y;
        if (get_subscripts(x, y, map_pair.second)) {
            if (output[x][y] == ". ")
                output[x][y] = map_pair.first.substr(0, 2);
            else
                output[x][y] = "* ";
        }
        else {
            if (exist_out_of_map)
                cout << ", " << map_pair.first;
            else {
                cout << map_pair.first;
                exist_out_of_map = true;
            }
        }
    }
    if (exist_out_of_map)
        cout << " outside the map" << endl;
    Cout_format_saver cfs;
    cout.precision(0);
    for (int i = 0; i < size; i++) {
        cout << setw(4);
        if ((size - i) % 3 == 1)
            cout << origin.y + scale * (size - i - 1);
        else
            cout << "";
        cout << ' ';
        for (int j = 0; j < size; j++)
            cout << output[j][size - i - 1];
        cout << endl;
    }
    for (int i = 0; i <= (size-1)/3 ; i++) {
        cout << "  " << setw(4) << origin.x + 3 * scale * i;
    }
    cout << endl;
}

void Map_view::clear()
{
    points.clear();
}

void Map_view::set_size(int size_)
{
    if (size_ <= 6)
        throw Error("New map size is too small!");
    if (size_ > 30)
        throw Error("New map size is too big!");
    size = size_;
}

void Map_view::set_scale(double scale_)
{
    if (scale_ <= 0.0)
        throw Error("New map scale must be positive!");
    scale = scale_;
}

void Map_view::set_origin(Point origin_)
{
    origin = origin_;
}

void Map_view::set_defaults()
{
    size = 25;
    scale = 2.0;
    origin = Point(-10, -10);
}

// Calculate the cell subscripts corresponding to the supplied location parameter,
// using the current size, scale, and origin of the display.
// This function assumes that origin is a  member variable of type Point,
// scale is a double value, and size is an integer for the number of rows/columns
// currently being used for the grid.
// Return true if the location is within the grid, false if not
bool Map_view::get_subscripts(int &ix, int &iy, Point location)
{
	// adjust with origin and scale
	Cartesian_vector subscripts = (location - origin) / scale;
	// truncate coordinates to integer after taking the floor
	// floor function will produce integer smaller than even for negative values,
	// so - 0.05 => -1., which will be outside the array.
	ix = int(floor(subscripts.delta_x));
	iy = int(floor(subscripts.delta_y));
	// if out of range, return false
	if ((ix < 0) || (ix >= size) || (iy < 0) || (iy >= size)) {
		return false;
    }
	else
		return true;
}
