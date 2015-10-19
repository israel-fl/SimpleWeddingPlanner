#include "hcal.h"

// Empty Constructor
HCal::HCal()
{
	// required empty constructor
}

// Function: addEvent
// Input: HEvent pointer
// Output: void
// Purpose: Adds an HEvent object to a vector of HEvents associated with
//			this particular instance of an HCal
void HCal::addEvent(HEvent* holiday) {
	events.add(holiday);
}

// Function: getVectSize
// Output: An integer with the size of the vector
// Purpose: Get the size of the vector of HEvents
int HCal::getVecSize() {
	return events.size() - 1;
}

// Function: getEvent
// Input: An integer with the index of the event we are looking for
// Output: an HEvent pointer
// Purpose: Return the HEvent inside the vector at the index specified
HEvent* HCal::getEvent(unsigned int eventDay){
	return events[eventDay];
}

// Function: search
// Input: an HEvent pointer
// Output: An integer indicating the result of the search
// Purpose: Calls for a binary search
int HCal::search(HEvent& day) {
	
	return binarySearchPart(day, 0, events.size() - 1);
	
}

// Function: binarySearchPart
// Input: an HEvent, an integer marking the start of the search
//		  and one marking the end of the index to search
// Output: an integer marking the result of the search
// Purpose: Helper function for the search function, contains the 
//			binary search algorithm
int HCal::binarySearchPart(HEvent& day, int start, int end) {

	if (end < start) {
		return -1;
	}

	int middleIndex = (end + start) / 2;
	HEvent* eventCompare = events[middleIndex];

	if (*eventCompare == day){
		return middleIndex;
	}

	if (*eventCompare > day) {
		return binarySearchPart(day, start, middleIndex - 1);
	}
	else {
		return binarySearchPart(day, middleIndex + 1, end);
	}

}

HCal::~HCal()
{
}
