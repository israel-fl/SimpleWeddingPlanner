#pragma once
#include <string>
#include <ostream>
#include "dateconv.h"

class HEvent
{
public:
	// Parametrized Constructor
	HEvent(unsigned long long& time, std::string& name, 
		std::string& type);

	unsigned long long epochTime;
	std::string holidayName;
	std::string holidayType;
	unsigned int year;
	unsigned int month;
	unsigned int day;
	
	// Friend functions

	// Overload << operator to display a HEvent object
	friend std::ostream& operator<<(std::ostream& os, HEvent& obj);

	// Overload a == operator to compare two HEvents for equality based on
	// epoch seconds
	friend bool operator==(HEvent first, HEvent second);

	// Overload a > and a < operator to compare two HEvents for inequality based on
	// epochh seconds
	friend bool operator>(HEvent first, HEvent second);
	friend bool operator<(HEvent first, HEvent second);


	// Destructor
	~HEvent();
};

