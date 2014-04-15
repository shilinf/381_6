#include "Computer_player.h"
#include "Model.h"
#include "Ship_factory.h"
#include "Island.h"
#include "Tanker.h"
#include <cstdlib>
#include <memory>
#include <set>

#include <iostream>
using std::string;
using std::shared_ptr;
using std::set;

using std::cout; using std::endl;
const int random_char_start = 97;
const int random_char_range = 26;

void Computer_player::init() 
{
    for (int i = 0; i < 4; ++i) {
        shared_ptr<Island> new_island(new Island(random_string_gen(), 
            Point(rand()%100, rand()%100), shared_from_this(),  1000, 200));
        Model::get_instance().add_island(new_island);
    }
}

bool Computer_player::run() 
{
    if (Model::get_instance().get_time() == 0) {
        shared_ptr<Ship> new_ship = create_ship(random_string_gen(), "Tanker", Point(10, 10), 
            shared_from_this());
        Model::get_instance().add_ship(new_ship);
        set<shared_ptr<Island>, Island_comp> ship_list = Model::get_instance().get_all_islands();
        auto it = ship_list.begin();
        new_ship->set_load_destination(*it);
        new_ship->set_unload_destination(*(++it));
    }
    return true;
}

string Computer_player::random_string_gen()
{
    string name;
    do {
        name.clear();
        for (int i = 0; i < 5; ++i) {
            name += random_char_start + rand()%random_char_range;
        }
    } while (Model::get_instance().is_name_in_use(name));
    return name;
}
