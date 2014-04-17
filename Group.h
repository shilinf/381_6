#ifndef GROUP_H
#define GROUP_H

/* Group stores weak_ptrs to its children, it overrides the Component's interfaces.
The update function updates its children by checking whether the child still exists.
*/

#include "Component.h"
#include <map>
#include <memory>

class Player;
class Island;
class Ship;

class Group : public Component {
public:
    Group(const std::string& name_, std::shared_ptr<Player> owner_ptr_) : 
        Component(name_, owner_ptr_) {}
    
    void update() override;
	
	void describe() const override;
    
    // There is no need for component to broadcast. No view show its information currently
	void broadcast_current_state() override {}
	
	/* Command functions */
    void set_destination_position_and_speed(Point destination_position, 
        double speed) override;

    void set_course_and_speed(double course, double speed) override;

    void stop() override;
	
    void dock(std::shared_ptr<Island> island_ptr) override;
	
    void refuel() override;
    
    void set_load_destination(std::shared_ptr<Island> island_ptr) override;
    
    void set_unload_destination(std::shared_ptr<Island> island_ptr) override;

    void attack(std::shared_ptr<Ship> in_target_ptr) override;

    void stop_attack() override;
    
    void set_terminus(Point position) override;
    
    void add_component(std::shared_ptr<Component> component_ptr) override;
    
    void remove_component(std::shared_ptr<Component> component_ptr) override;
    
    void disband() override;
    
    // check whether this contains component_ptr
    void check_contain_component(std::shared_ptr<Component> component_ptr) override;
    
private:
    std::map<std::string, std::weak_ptr<Component> > children;
};

#endif
