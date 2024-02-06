#include "Child.h"
//child.cpp
Child::Child()
    :age_{ 10 }
{
    this->name_ = "child";
    std::cout << "\n***child constructor\n";
}

Child::~Child()
{
    std::cout << "\n***child destructor\n";
}
std::ostream& operator<<(std::ostream& os, const Child& child)
{
    os << child.name_ << " child: " << child.age_;
    return os;
}
