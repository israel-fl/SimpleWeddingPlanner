// ITP 365 Fall 2015
// HW4 - Wedding Planner
// Name: Israel Flores
// Email: israelfl@usc.edu
// Platform: Windows

#include "hcal.h"
#include "hevent.h"
#include <string>
#include <iostream>
#include <fstream>

// Function: loadCal
// Input: A string with the name of the file
// Output: Returns a dynamically allocated Calendar object
// Purpose: Read a csv file and dynamically create HEvent objects, then 
//			store them inside a vector of an HCal object
HCal* loadCal(std::string& file) {

	HCal* calendar = new HCal();

	std::ifstream fileInput(file);

	if (fileInput.is_open()) {

		int lineCount = 0;
		
		while (!fileInput.eof()) {
			
			std::string line;
			std::getline(fileInput, line);

			// To account for \n at end of file
			if (line.size() == 0) {
				break;
			}
			// To parse out the description line (i.e. Epoch,Holiday name,Holiday type)
			// So that we won't make an event that simply contains descriptions
			else if (lineCount == 0) {
				lineCount++;
			}
			else {

				std::string timeString, name, type;
				int delim = line.find(","); // defining a delimiter
				timeString = line.substr(0, delim);
				line = line.substr(delim + 1);
				delim = line.find(",");
				name = line.substr(0, delim);
				type = line.substr(delim + 1);

				unsigned long long time = std::stoi(timeString);

				calendar->addEvent(new HEvent(time, name, type)); 

			} //else if

		} //while

	}
	else {
		std::cout << "ERROR: FILE NOT FOUND" << std::endl;
	} // else if

	return calendar;
}

// Function: mergeCal
// Input: Two calendar object pointers
// Output: A new HCal object dynamically allocated
// Purpose: Merge both HCal 1 and HCal 2 into a third HCal
HCal* mergeCal(HCal* cal1, HCal* cal2) {

	HCal* C = new HCal();
	int i = 0;
	int j = 0;
	bool isDone = false;
	int remainingDaysA;
	int remainingDaysB;

	while (!isDone) {

		if (cal1->getEvent(i) < cal2->getEvent(j)) {

			C->addEvent(cal1->getEvent(i));

			i++;

			if (i > cal1->getVecSize()) {
				break;
			}

		}

		else if (cal1->getEvent(i) > cal2->getEvent(j)) {

			C->addEvent(cal2->getEvent(j));

			j++;

			if (j > cal2->getVecSize()) {
				break;
			}

		} // else if 

		remainingDaysA = cal1->getVecSize() - i;
		remainingDaysB = cal2->getVecSize() - j;

	} // while
	

		// if only one calendar has remaining days
		if (remainingDaysA > 0) {
			for (int a = 0; a < remainingDaysA; a++) {
				C->addEvent(cal1->getEvent(i));
				i++;
			}
		}
		else if (remainingDaysB > 0) {
			for (int a = 0; a < remainingDaysB; a++) {
				C->addEvent(cal2->getEvent(j));
				j++;
			}
		} // else if
	
		return C; // return new calendar

	}



// Main

int main(int argc, char** argv)
{

	// files
	std::string bra15 = "BRHol2015.csv";
	std::string bra16 = "BRHol2016.csv";
	std::string india15 = "INHol2015.csv";
	std::string india16 = "INHol2016.csv";
	std::string US15 = "USHol2015.csv";
	std::string US16 = "USHol2016.csv";

	// Load functions
	HCal* calBrazil15 = loadCal(bra15);
	HCal* calBrazil16 = loadCal(bra16);
	HCal* calIndia15 = loadCal(india15);
	HCal* calIndia16 = loadCal(india16);
	HCal* calUS15 = loadCal(US15);
	HCal* calUS16 = loadCal(US16);

	// Merging calendars
	HCal* brazilFinal = mergeCal(calBrazil15, calBrazil16);
	HCal* indiaFinal = mergeCal(calIndia15, calIndia16);
	HCal* usFinal = mergeCal(calUS15, calUS16);

	HCal* indiaBrazil = mergeCal(brazilFinal, indiaFinal);
	HCal* finalCalendar = mergeCal(indiaBrazil, usFinal);

	std::string userDate;
	bool isDone = false;

	// Interface
	while (!isDone) {
		
		std::cout << "Welcome to the wedding planner! \nPlease enter a date (MM/YY/DD):" 
			<< std::endl;

		std::cin >> userDate;

		// Select 'q' to quit
		if (userDate == "q" || userDate == "Q") {
			isDone = true;
			std::cout << "Quitting!" << std::endl;
		}
		
		else if (userDate != "") {

			std::string monthString = userDate.substr(0, 2);
			unsigned int month = std::stoi(monthString);

			std::string dayString = userDate.substr(3, 5);
			unsigned int day = std::stoi(dayString);

			std::string yearString = userDate.substr(6);
			unsigned int year = std::stoi(yearString);

			// Substracting to compensate for PST time
			unsigned long long weddingDate = getEpochSecs(month, day, year) - 25200;
			
			// Compensate for Daylight Savings Time 
			// Ends
			if (weddingDate < 1425780000) { 
				weddingDate -= 3600; // 3600 seconds in an hour 
			}
			// Begins
			else if (weddingDate >= 1425780000 && weddingDate < 1446343200) {
				weddingDate += 3600;
			}
			// Ends
			else if (weddingDate >= 1446343200 && weddingDate < 1457834400) {
				weddingDate -= 3600;
			}
			// Begins
			else if (weddingDate >= 1457834400 && weddingDate < 1478397600) {
				weddingDate += 3600;
			}
			// Ends
			else {
				weddingDate -= 3600;
			} // else ifs for Daylight savings

			std::string weddingString = "Wedding";
			std::string weddingType = "Special Occassion";

			HEvent wedding = HEvent(weddingDate, weddingString, weddingType);

			int result = finalCalendar->search(wedding);

			// Manage search result
			if (result == -1) {
				std::cout << "That's a great day for a wedding!" << std::endl;
			}
			else {
				HEvent* busy = finalCalendar->getEvent(result);
				std::cout << userDate << " is " << *busy << std::endl;
			} // else if

		} // else if

	} // while

	return 0;
}
