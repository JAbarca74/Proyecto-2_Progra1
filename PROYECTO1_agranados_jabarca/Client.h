#pragma once
#include <iostream>
#include <string>
#include "DateProcessorTool.h"
#define RED "\033[31m"
#define YELLOW "\033[33m" 
#define GREEN "\033[32m"
#define RESET "\033[0m"
using namespace std;
class Client
{
private:
	string identification;
	string personName;
	string birthdayDate;
	string* reservedSeats;
	int numberOfSeats;
	float totalInvoice;
	float applyDiscount;
	string* collectIdentification;
	int totalCollectIdentification;
	DateProcessorTool dateProcessorTool;

public:
	Client() : personName(""), identification(""), birthdayDate(""), reservedSeats(nullptr), numberOfSeats(0),
		collectIdentification(nullptr), totalCollectIdentification(0), dateProcessorTool(), totalInvoice(0.0), applyDiscount(0.0) {
	};
	void collectAllInformation();
	void addIdentificationList(string identification);
	bool isValidClient(string identification);
	void validateID(string id);
	void addReservedSeat(const string& seatCode);
	void showReservedSeats();
	void setNumberOfSeats(int aNumber);
	int getNumberOfSeats();
	string getIdentification();
	string getPersonName();
	string getBirthdayDate();
	float getTotalInvoce();
	float getApplyDiscount();
	void setTotalInvoice(float anAmount);
	void setApplyDiscount(float anAmount);
	void cleanIdentificationList();
	void inputSum(float price);
};
