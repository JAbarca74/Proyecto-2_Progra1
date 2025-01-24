#include "DateProcessorTool.h"

void DateProcessorTool::confirmDateBirthDay(string& dateTemporal)
{
	while (true)
	{
		if (isDateValid(dateTemporal))
		{
			if (isAdult(dateTemporal))
			{
				checkDateComponents(dateTemporal);
				if (isValidMonth() && isValidDay())
				{
					break;
				}
			}
			else
			{
				cout << RED << "ERROR. " << RESET << "Debes ser mayor de edad." << endl;
			}
		}
		else
		{
			cout << RED << "ERROR. " << RESET << "(debe tener formato DD/MM/YYYY)." << endl;
		}
		cout << RED << "La fecha no es valida " << RESET << "Ingrese una fecha de nacimiento valida: ";
		cin >> dateTemporal;
	}
}

void DateProcessorTool::checkDateComponents(string& dateTemporal)
{
	string dayPart = dateTemporal.substr(0, 2);
	string monthPart = dateTemporal.substr(3, 2);
	string yearPart = dateTemporal.substr(6, 4);
	yearTemporal = stoi(yearPart);
	monthTemporal = stoi(monthPart);
	dayTemporal = stoi(dayPart);
}

void DateProcessorTool::updateCurrentDate()
{
	time_t now = time(0);
	tm localTime;
	localtime_s(&localTime, &now);

	currentDay = localTime.tm_mday;
	currentMonth = localTime.tm_mon + 1;
	currentYear = localTime.tm_year + 1900;
}

bool DateProcessorTool::isDateValid(string& dateTemporal)
{
	if (dateTemporal.size() != 10 || dateTemporal[2] != '/' || dateTemporal[5] != '/')
	{
		return false;
	}
	for (int i = 0; i < dateTemporal.size(); i++)
	{
		if (i == 2 || i == 5)
		{
			continue;
		}
		if (dateTemporal[i] < '0' || dateTemporal[i] > '9')
		{
			return false;
		}
	}
	return true;
}

bool DateProcessorTool::isLeapYear()
{
	if ((yearTemporal % 4 == 0 && yearTemporal % 100 != 0) || (yearTemporal % 400 == 0))
	{
		return true;
	}
	return false;
}

bool DateProcessorTool::isValidMonth()
{
	if (monthTemporal >= 1 && monthTemporal <= 12)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool DateProcessorTool::isValidDay()
{
	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	if (monthTemporal == 2 && isLeapYear())
	{
		daysInMonth[1] = 29;
	}
	if (dayTemporal >= 1 && dayTemporal <= daysInMonth[monthTemporal - 1])
	{
		return true;
	}
	return false;
}

bool DateProcessorTool::isAdult(string& dateTemporal)
{
	updateCurrentDate();
	checkDateComponents(dateTemporal);
	int age = currentYear - yearTemporal;

	if (currentMonth < monthTemporal || (currentMonth == monthTemporal && currentDay < dayTemporal)) {
		age--;
	}
	if (age >= 18) {
		return true;
	}
	return false;
}

bool DateProcessorTool::isFutureDateEvent(string& dateTemporal)
{
	updateCurrentDate();
	checkDateComponents(dateTemporal);
	if (yearTemporal > currentYear) {
		return true;
	}
	else if (yearTemporal < currentYear) {
		return false;
	}
	if (monthTemporal > currentMonth) {
		return true;
	}
	else if (monthTemporal < currentMonth) {
		return false;
	}
	if (dayTemporal > currentDay) {
		return true;
	}
	return false;
}

void DateProcessorTool::confirmDateEvent(string& dateTemporal)
{
	while (true)
	{
		if (isDateValid(dateTemporal))
		{
			if (isFutureDateEvent(dateTemporal))
			{
				checkDateComponents(dateTemporal);
				if (isValidMonth() && isValidDay())
				{
					break;
				}
			}
			else
			{
				cout << RED << "ERROR. " << RESET << "Debes ser fecha futura" << endl;
			}
		}
		else
		{
			cout << RED << "ERROR. " << RESET << "(debe tener formato DD/MM/YYYY)." << endl;
		}
		cout << RED << "La fecha no es valida " << RESET << "Ingrese una fecha de evento valida: ";
		cin >> dateTemporal;
	}
}


