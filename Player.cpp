#include "Player.h"
#include "Utility.h"

void Player::use_resource(int resource_needed)
{
    if (resource_needed > resource)
        throw Error("Resource is not enough to create this ship!");
    else
        resource -= resource_needed;
}

