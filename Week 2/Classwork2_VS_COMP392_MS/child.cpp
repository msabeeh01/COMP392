#include <iostream>
#include "child.hpp"
Child::Child()
:age_{ 10 }
{
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
