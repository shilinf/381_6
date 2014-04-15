#include "Sim_object.h"
#include "Geometry.h"
#include "Utility.h"

Point Sim_object::get_location() const
{
    throw Error("Cannot get location!");
}
