#include "Sailing_view.h"
#include "Utility.h"
#include <cmath>
#include <vector>
#include <iomanip>
#include <iostream>


using std::cout; using std::endl;
using std::vector;
using std::string;
using std::ios; using std::setw;
using std::streamsize;

const int sailing_view_field_width_c = 10;

void Sailing_view::update_fuel(const std::string& name, double fuel)
{
    ships_info[name].fuel = fuel;
}


void Sailing_view::update_course(const std::string& name, double course)
{
    ships_info[name].cs.course = course;
}

void Sailing_view::update_speed(const std::string& name, double speed)
{
    ships_info[name].cs.speed = speed;
}

void Sailing_view::update_remove(const std::string& name)
{
    ships_info.erase(name);
}

void Sailing_view::draw()
{
    cout << "----- Sailing Data -----" << endl;
    cout << setw(sailing_view_field_width_c) << "Ship" << setw(sailing_view_field_width_c)
    << "Fuel" << setw(sailing_view_field_width_c) << "Course"
    << setw(sailing_view_field_width_c) << "Speed" << endl;
    for (auto& map_pair : ships_info)
        cout << setw(sailing_view_field_width_c) << map_pair.first
        << setw(sailing_view_field_width_c)
        << map_pair.second.fuel << setw(sailing_view_field_width_c)
        << map_pair.second.cs.course << setw(sailing_view_field_width_c)
        << map_pair.second.cs.speed << endl;
}

void Sailing_view::clear()
{
    ships_info.clear();
}