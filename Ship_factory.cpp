#include "Ship_factory.h"
#include "Geometry.h"
#include "Utility.h"
#include "Tanker.h"
#include "Cruiser.h"
#include "Cruise_ship.h"
#include "Refuel_ship.h"
#include "Player.h"

using std::shared_ptr;
using std::string;

shared_ptr<Ship> create_ship(const string& name, const string& type, Point initial_position, shared_ptr<Player> owner_ptr)
{
    if (type == "Cruiser") {
        owner_ptr->use_resource(150);
        return shared_ptr<Ship>(new Cruiser(name, initial_position, owner_ptr));
    }
    else if (type == "Tanker") {
        owner_ptr->use_resource(100);
        return shared_ptr<Ship>(new Tanker(name, initial_position, owner_ptr));
    }
    else if (type == "Cruise_ship") {
        owner_ptr->use_resource(200);
        return shared_ptr<Ship>(new Cruise_ship(name, initial_position, owner_ptr));
    }
    else if (type == "Refuel_ship") {
        owner_ptr->use_resource(100);
        return shared_ptr<Ship>(new Refuel_ship(name, initial_position, owner_ptr));
    }
    else
        throw Error("Trying to create ship of unknown type!");
}
