#pragma once
#include <iostream>
#include <string>
#include <ctime> 
#define RED "\033[31m"
#define RESET "\033[0m"
using namespace std;
class DateProcessorTool
{
private:
	int dayTemporal;
	int monthTemporal;
	int yearTemporal;
	int currentDay;
	int currentMonth;
	int currentYear;
public:
	DateProcessorTool() : dayTemporal(0), monthTemporal(0), yearTemporal(0), currentDay(0), currentMonth(0),
		currentYear(0) {
	};
	void confirmDateBirthDay(string& dateTemporal);
	void checkDateComponents(string& dateTemporal);
	void updateCurrentDate();
	bool isDateValid(string& dateTemporal);
	bool isLeapYear();
	bool isValidMonth();
	bool isValidDay();
	bool isAdult(string& dateTemporal);
	bool isFutureDateEvent(string& dateTemporal);
	void confirmDateEvent(string& dateTemporal);
};
