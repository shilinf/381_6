#ifndef HUMAN_PLAYER_H
#define HUMAN_PLAYER_H

/* The Human Player class is responsible for controlling the Model and Views 
according to interactions with the user.
*/

#include "Player.h"
#include <string>
#include <map>
#include <vector>
#include <memory>

class View;
class Map_view;
class Sailing_view;
class Bridge_view;
class Destination_view;
class Island;
class Component;
struct Point;

class Human_player : public Player {
public:
    Human_player(const std::string& name_);
    
    void init() override;
    
	bool run() override;
    
private:
    std::shared_ptr<Map_view> map_view_ptr;
    std::shared_ptr<Sailing_view> sailing_view_ptr;
    std::shared_ptr<Destination_view> destination_view_ptr;
    std::map<std::string, std::shared_ptr<Bridge_view>> bridge_view_container;
    std::vector<std::shared_ptr<View>> draw_view_order;
    std::shared_ptr<Component> target_component; // component pointer for component commands
    std::map<std::string, void(Human_player::*)()> commands_map;
    
    // command functions
    void open_map_view();
    void close_map_view();
    void open_sailing_view();
    void close_sailing_view();
    void open_bridge_view();
    void close_bridge_view();
    void open_destination_view();
    void close_destination_view();
    void restore_default_map();
    void set_map_size();
    void set_map_scale();
    void set_map_origin();
    void draw_map();
    void show_object_status();
    void create_new_ship();
    void create_new_group();
    void quit();
    
    // control component command functions
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
    void set_component_terminus();
    void add_group_component();
    void remove_group_component();
    void disband_group();

    // helper functions
    Point read_point();
    double read_double();
    double read_check_speed();
    std::string read_string();
    void check_map_view_exist();
    std::shared_ptr<Island> read_get_island();
    std::string read_check_name();
    void remove_view(std::shared_ptr<View> view);
    void discard_input_remainder();
};

#endif
