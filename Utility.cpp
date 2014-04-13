#include "Utility.h"
#include "Island.h"
#include "Ship.h"

bool Island_comp::operator() (const std::shared_ptr<Island> island1,
                 const std::shared_ptr<Island> island2) const
{
    return island1->get_name() < island2->get_name();
}

//ssx
bool Ship_comp::operator() (const std::shared_ptr<Ship> ship1, 
                            const std::shared_ptr<Ship> ship2) const
{
    return ship1->get_name() < ship2->get_name();
}
