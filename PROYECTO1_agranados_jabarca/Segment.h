#pragma once
#include <iostream>
#include <string>
#define GREEN "\033[32m"
#define RED "\033[31m"
#define RESET "\033[0m"
using namespace std;
class Segment
{
private:
	int numberSeatingRows;
	int numberSeatingColumns;
	float price;
	string** seats;

public:
	Segment() : numberSeatingRows(0), numberSeatingColumns(0), price(0.0), seats(nullptr) {
	};
	int getNumberSeatingRows();
	int getNumberSeatingColumns();
	float getPrice();
	void updateData(int numberSeatingRows_, int numberSeatingColumns_, float price_);
	void printSeats();
	bool reserveSeat(string seatCode);
	bool isFullTheEvent();
	void clearSeats();
	~Segment();
};