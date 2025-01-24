#pragma once
#include "DateProcessorTool.h"
#include "Segment.h"
#include "Client.h"
#include <iostream>
#include <string>
#define RED "\033[31m"
#define BRIGHT_YELLOW "\033[93m"
#define GREEN "\033[32m"
#define BRIGHT_CYAN "\033[96m" 
#define YELLOW "\033[33m" 
#define BRIGHT_WHITE "\033[97m"
#define LIGHT_PURPLE "\033[1;95m"
#define RESET "\033[0m"
using namespace std;

class ConfigEvent {
private:
	int segmentsEvent;
	int sizeSegmentsSpace;
	int totalRows;
	int totalColumns;
	int discountedTicketsSold;
	int acountWithDiscount;
	int discount;
	int codes;
	int freeSeats;
	string nameEvent;
	string dateEvent;
	string reserveSeats;
	string separatorIdeas;
	List<string> discountCodes;
	List<List<string>*> availableSeats;
	Segment segment;
	List<Segment> segmentsSpace;
	Client client;
	DateProcessorTool dateProcessorTool;

public:
	ConfigEvent() : nameEvent("-"), dateEvent("-"), segmentsEvent(0), freeSeats(),
		sizeSegmentsSpace(0), segmentsSpace(), totalRows(0), totalColumns(0), availableSeats(), reserveSeats(""),
		discountedTicketsSold(0), acountWithDiscount(0), discount(0), discountCodes(), codes(0), client(), segment(), dateProcessorTool(),
		separatorIdeas("--------------------//----------------------") {
	};
	void printSeparatorIdeas();
	void printInicializeEventData();
	void confirmSegment();
	int getSizeSegmentsSpace();
	int calculateTotalSeats();
	void resizeSegmentsSpace(int newSize);
	void prepareEventData();
	void printExportCurrentEvent();
	void deleteEvent();
	void configureMatrixDimensions(int segmentNumber);
	void inicializateSeatsSpace(int segmentNumber);
	void createdSegmentSeats();
	void printSegment();
	void getReserveSeat(string& reserveSeats);
	void showAvaibleSeats();
	void createVectorDiscounts(int size);
	void generateDiscountCodes();
	void printCodes();
	void deleteCode(string code);
	float applyCodeDiscount(Segment* spaceSegment);
	void processPurchase(int seatsPurchased, string& numberReserveSeats);
	void numberOfSeatsPurchase();
	void controlTicketSoldEvent();
	void reserveSeatInSegment(int segmentIndex, const string& seatCode);
	void showStatusOfEvent();
	Segment* getSegment(int pos);
	bool isSegmentExist();
	bool isDiscountNumExist();
	bool isCodeExist(string code);
	bool isSeatAvailable(string& reserveSeats);
	bool isFullEvent();
	void captureEventData(int& temporalRows, int& temporalColumns, float temporalPrice);
	void printInvoice(int seatsPurchased, float anApplyDiscount, float aTotalPrice, float anFinalPrice);
	void aboutUs();
	~ConfigEvent();
};
