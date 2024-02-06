#include<iostream>
class Date {
public:
	Date() {}
	Date(int year, int month, int day) {
		this->_year = year;
		this->_month = month;
		this->_day = day;
	}

	Date operator+(const int day) {
		return Date{ _year, _month, _day + day };
	}
	Date operator+(const Date& otherDate) {
		return Date{ _year + otherDate._year,_month + otherDate._month,_day + otherDate._day };
	}
	friend std::ostream& operator<<(std::ostream& os, const Date& dt) {
		os << '<' << dt._year << '-' << dt._month << '-' << dt._day << '>';
	}
private:
	int _year;
	int _month;
	int _day;
};

