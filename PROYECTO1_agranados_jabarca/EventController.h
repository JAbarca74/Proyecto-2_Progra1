#pragma once
#include "ConfigEvent.h"
#include <iostream>
#include <string>
#define WHITE "\033[97m" 
#define RED "\033[31m"
#define GREEN "\033[32m"
#define BLUE "\033[34m"
#define YELLOW "\033[33m"
#define LIGHT_BLUE "\033[36m"
#define BRIGHT_RED "\033[91m"
#define BRIGHT_GREEN "\033[92m" 
#define BRIGHT_YELLOW "\033[93m"
#define BRIGHT_BLUE "\033[94m"
#define BRIGHT_PURPLE "\033[95m"
#define BRIGHT_CYAN "\033[96m"
#define BRIGHT_WHITE "\033[97m"
#define ORANGE "\033[38;5;214m" 
#define RESET "\033[0m"

using namespace std;
class EventController
{
private:
	int userOption;
	int spaceText;
	ConfigEvent configEvent;
	Segment segment;
	void printPrincipalMenu();
	void printConfigMenu();
	void printConfigPriceDiscountMenu();
	void printTicketSellMenu();
	void printShowSegmentSeatsFlow(const int& segmentNumber);
	void validateUserOption(int& userOption);
	void captureMenuOption();
	void controlConfigMenuFlow();
	void controlPriceDiscountMenuFlow();
	void controlTicketSellMenuFlow();
	void controlShowSegmentSeatsFlow();
	void printAboutUs();

public:
	EventController() : userOption(0), spaceText(0), configEvent(), segment() {
	};
	void controlPrincipalMenuFlow();
};
