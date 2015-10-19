#include "hevent.h"

// Paramterized Constructor
HEvent::HEvent(unsigned long long& time, std::string& name,
	std::string& type) {

	epochTime = time;
	holidayName = name;
	holidayType = type;

	year = getYear(epochTime);
	month = getMonth(epochTime);
	day = getMonthDay(epochTime);


}

// Overload << operator to display a HEvent object
std::ostream& operator<<(std::ostream& os, HEvent& obj) {
	
	os << obj.holidayName << " (" << obj.holidayType << ")";

	return os;
}

// Overload a == operator to compare two HEvents for equality based on
// epoch seconds
bool operator==(HEvent first, HEvent second) {

	if (first.epochTime == second.epochTime) {
		return true;
	}
	else {
		return false;
	}

}

// Overload a > operator to compare two HEvents for inequality based on
// epochh seconds
bool operator>(HEvent first, HEvent second) {

	if (first.epochTime > second.epochTime) {
		return true;
	}
	else {
		return false;
	}

}

// Overload a < operator to compare two HEvents for inequality based on
// epochh seconds
bool operator<(HEvent first, HEvent second) {

	if (first.epochTime < second.epochTime) {
		return true;
	}
	else {
		return false;
	}

}


// Destructor
HEvent::~HEvent()
{
}
