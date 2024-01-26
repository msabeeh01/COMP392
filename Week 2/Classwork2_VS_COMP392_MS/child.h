#include <iostream>
#include "parent.h"
#pragma once
class Child : public Parent //child will get all members as is
{
public:
Child();
~Child();
friend std::ostream& operator<<(std::ostream&, const Child&);
private:
int age_;
};