#include "Utility.h"
#include "Sim_object.h"

bool Sim_object_comp::operator() (const std::shared_ptr<Sim_object> sim_object1,
                 const std::shared_ptr<Sim_object> sim_object2) const
{
    return sim_object1->get_name() < sim_object2->get_name();
}
