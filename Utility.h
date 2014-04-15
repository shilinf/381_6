#ifndef UTILITIES_H
#define UTILITIES_H

#include <exception>
#include <memory>

class Sim_object;

class Error : public std::exception {
public:
	Error(const char* msg_) : msg(msg_) {}
    const char* what() const noexcept override
        {return msg;}
private:
	const char* msg;
};

struct Sim_object_comp {
    bool operator() (const std::shared_ptr<Sim_object> sim_object1,
                     const std::shared_ptr<Sim_object> sim_object2) const;
};

#endif
