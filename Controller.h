#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "Participant.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

/* Controller
This class is responsible for controlling the Model and View according to interactions
with the user.
*/

class View;
class Map_view;
class Sailing_view;
class Bridge_view;
class Destination_view;
class Island;
class Component;
class Controller;
struct Point;

using Command_map_t = std::map<std::string, void(Controller::*)()>;

class Controller : public Participant {
public:
    Controller(std::string name_);
    
    void init() override;
    
	// create View object, run the program by acccepting user commands, then destroy View object
	void run() override;
    
private:
    std::shared_ptr<Map_view> map_view_ptr;
    std::shared_ptr<Sailing_view> sailing_view_ptr;
    std::shared_ptr<Destination_view> destination_view_ptr;
    std::map<std::string, std::shared_ptr<Bridge_view>> bridge_view_container;
    std::vector<std::shared_ptr<View>> draw_view_order;
    std::shared_ptr<Component> target_component; // ship pointer for ship commands
    Command_map_t commands_map;
    
    // command functions
    void open_map_view();
    void close_map_view();
    void open_sailing_view();
    void close_sailing_view();
    void open_bridge_view();
    void close_bridge_view();
    void open_destination_view();
    void close_destination_view();
    void set_map_size();
    void set_map_scale();
    void set_map_origin();
    void draw_map();
    void show_object_status();
    void update_all_objects();
    void create_new_ship();
    void create_new_group();
    void quit();
    
    // control ship command functions

	//ssx
    void set_component_terminus();
    void set_component_course();
    void set_component_to_position();
    void set_component_destination_island();
    void set_component_load_island();
    void set_component_unload_island();
    void set_component_dock_island();
    void set_component_attack_target();
    void set_component_refuel();
    void set_component_stop();
    void set_component_stop_attack();
    void remove_group_component();
    void add_group_component();
    void disband_group();

    // helper functions
    Point read_point();
    double read_double();
    double read_check_speed();
    std::string read_string();
    void check_map_view_exist();
    std::shared_ptr<Island> read_get_island();
    void remove_view(std::shared_ptr<View> view);
    void discard_input_remainder();
    void restore_default_map();
};

#endif






