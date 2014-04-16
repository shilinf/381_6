#include "Computer_player.h"
#include "Model.h"
#include "Ship_factory.h"
#include "Island.h"
#include "Ship.h"
#include <cstdlib>
#include <memory>
#include <set>
#include <iostream>

using std::string;
using std::shared_ptr;
using std::set;
using std::cout; using std::endl;

const int random_char_start_c = 97;
const int random_char_range_c = 26;

void Computer_player::init() 
{
    for (int i = 0; i < 4; ++i) {
        shared_ptr<Island> new_island(new Island(random_string_gen(), 
            Point(rand()%60, rand()%60), shared_from_this(),  1000, 200));
        Model::get_instance().add_island(new_island);
    }
    cout << get_name() << " has created 4 islands" << endl;
}

bool Computer_player::run() 
{
    cout << "\nTime " << Model::get_instance().get_time() 
            << ": Computer player did commands" << endl;
    if (Model::get_instance().get_time() == 0) {
        
        set<shared_ptr<Island>, Sim_object_comp> ship_list = Model::get_instance().get_all_islands();
        
        shared_ptr<Ship> new_ship = create_ship(random_string_gen(), "Tanker", Point(10, 10), 
            shared_from_this());
        Model::get_instance().add_ship(new_ship);
        auto it = ship_list.begin();
        new_ship->set_load_destination(*it);
        new_ship->set_unload_destination(*(++it));

        new_ship = create_ship(random_string_gen(), "Cruise_ship", Point(20, 20),
            shared_from_this());
        Model::get_instance().add_ship(new_ship);
        new_ship->set_destination_position_and_speed((*(++it))->get_location(), 10);
        
        new_ship = create_ship(random_string_gen(), "Refuel_ship", Point(30, 30), 
            shared_from_this());
        Model::get_instance().add_ship(new_ship);
        new_ship->set_load_destination(*(++it));    
    
    }
    return true;
}

string Computer_player::random_string_gen()
{
    string name;
    do {
        name.clear();
        for (int i = 0; i < 5; ++i) {
            name += random_char_start_c + rand()%random_char_range_c;
        }
    } while (Model::get_instance().is_name_in_use(name));
    return name;
}
