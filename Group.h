#ifndef GROUP_H
#define GROUP_H

#include "Component.h"
#include <set>
#include <memory>

class Ship;

class Group : public Component {
public:
    Group(const std::string& name_) : Component(name_) {}
    
    void update() override;
	
	void describe() const override;
	
	void broadcast_current_state() override;
	
	/*** Command functions ***/
    void set_destination_position_and_speed(Point destination_position, double speed) override;
	
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
    
    //void get_all_contained_component(std::set<std::shared_ptr<Component> >& all_components) override;
    
    //void contain_component(std::shared_ptr<Component> component_ptr);
private:
    std::set<std::shared_ptr<Component> > children;
};

#endif
