//parent.hpp
#include <iostream>
class Parent
{
public:
	Parent();
	~Parent();
	friend std::ostream& operator<<(std::ostream&, const Parent&);
protected:
	std::string name_;
};
