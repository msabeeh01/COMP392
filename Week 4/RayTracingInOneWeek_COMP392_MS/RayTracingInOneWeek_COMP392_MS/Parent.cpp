#include "Parent.h"
//parent.cpp
Parent::Parent() :name_{ "parent" }
{
    std::cout << "\n***parent constructor\n";
}

Parent::~Parent()
{
    std::cout << "\n***parent destructor\n";
}
std::ostream& operator<<(std::ostream& os, const Parent& parent)
{
    os << "Parent: " << parent.name_;
    return os;
}
