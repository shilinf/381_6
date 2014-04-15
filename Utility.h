#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>
#include <memory>

class Island;
class Ship;
class Component;

class Error : public std::exception {
public:
	Error(const char* msg_) : msg(msg_) {}
    const char* what() const noexcept override
        {return msg;}
private:
	const char* msg;
};

struct Island_comp {
    bool operator() (const std::shared_ptr<Island> island1,
                     const std::shared_ptr<Island> island2) const;
};

// ssx
struct Ship_comp {
    bool operator() (const std::shared_ptr<Ship> ship1,
                     const std::shared_ptr<Ship> ship2) const;
};

struct Component_comp {
    bool operator() (const std::shared_ptr<Component> component1,
                     const std::shared_ptr<Component> component2) const;
}; 

#endif
