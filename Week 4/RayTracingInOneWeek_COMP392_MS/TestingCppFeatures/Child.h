#pragma once
#include "Parent.h"
#include<iostream>
//child.hpp
class Child : public Parent //child will get all members as is
{
public:
    Child();
    ~Child();
    friend std::ostream& operator<<(std::ostream&, const Child&);

private:
    int age_;
};

