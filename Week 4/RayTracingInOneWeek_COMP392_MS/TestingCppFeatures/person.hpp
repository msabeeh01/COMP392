//person.hpp
#pragma once
class HostClass {
public:

private:
	friend class ClientClass; //this class will have access to all members of HostClass 
	friend float calculate_tax(float); //this method will have the same access
};
