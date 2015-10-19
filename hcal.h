#pragma once
#include "hevent.h"
#include "vector.h"


class HCal
{
public:

	// Empty constructor
	HCal();

	
	Vector<HEvent*> events;

	// Function: addEvent
	// Input: HEvent pointer
	// Output: void
	// Purpose: Adds an HEvent object to a vector of HEvents associated with
	//			this particular instance of an HCal
	void addEvent(HEvent* holiday);

	// Function: getVectSize
	// Output: An integer with the size of the vector
	// Purpose: Get the size of the vector of HEvents
	int getVecSize();

	// Function: getEvent
	// Input: An integer with the index of the event we are looking for
	// Output: an HEvent pointer
	// Purpose: Return the HEvent inside the vector at the index specified
	HEvent* getEvent(unsigned int eventDay);

	// Function: search
	// Input: an HEvent pointer
	// Output: An integer indicating the result of the search
	// Purpose: Calls for a binary search
	int search(HEvent& day);

	// Function: binarySearchPart
	// Input: an HEvent, an integer marking the start of the search
	//		  and one marking the end of the index to search
	// Output: an integer marking the result of the search
	// Purpose: Helper function for the search function, contains the 
	//			binary search algorithm
	int binarySearchPart(HEvent& day, int start, int end);

	// Destructor
	~HCal();
};

