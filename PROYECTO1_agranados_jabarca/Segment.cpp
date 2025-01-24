#include "Segment.h"

Segment::~Segment()
{
    clearSeats();
}

int Segment::getNumberSeatingRows()
{
    return numberSeatingRows;
}

int Segment::getNumberSeatingColumns()
{
    return numberSeatingColumns;
}

float Segment::getPrice()
{
    return price;
}

string Segment::updateData(int numberSeatingRows_, int numberSeatingColumns_, float price_)
{
    numberSeatingRows = numberSeatingRows_;
    numberSeatingColumns = numberSeatingColumns_;
    price = price_;

    // Clear existing seats
    while (seats.getHead() != nullptr) {
        seats.deleteNode(0);
    }

    // Generate seat labels and add to list
    for (int position = 0; position < numberSeatingRows * numberSeatingColumns; position++) {
        int letter = position / numberSeatingColumns;
        int number = position % numberSeatingColumns;

        string seatLabel;
        if (letter < 26) {
            seatLabel = string(1, 'A' + letter);
        }
        else {
            char firstLetter = 'A' + (letter / 26) - 1;
            char secondLetter = 'A' + (letter % 26);
            seatLabel = string(1, firstLetter) + string(1, secondLetter);
        }

        seats.addNewNode(seatLabel + to_string(number + 1));
    }

    return "Seats initialized";
}

void Segment::printSeats() {

    Node<string>* currentNode = seats.getHead();
    int count = 0;

    while (currentNode != nullptr) {
        string seatLabel = currentNode->getElement();

        if (seatLabel != "XX") {
            cout << GREEN << "[ |_" << seatLabel << "_| ] " << RESET;
        }
        else {
            cout << RED << "[ |_" << seatLabel << "_| ] " << RESET;
        }

        count++;
        if (count % numberSeatingColumns == 0) {
            cout << endl;
        }

        currentNode = currentNode->getNext();
    }
    cout << endl;
}

bool Segment::reserveSeat(string seatCode)
{
    Node<string>* currentNode = seats.getHead();
    int position = 0;

    while (currentNode != nullptr) {
        if (currentNode->getElement() == seatCode) {
            currentNode->setElement("XX");
            return true;
        }
        currentNode = currentNode->getNext();
        position++;
    }
    return false;
}


bool Segment::isFullTheEvent()
{
    Node<string>* currentNode = seats.getHead();

    while (currentNode != nullptr) {
        if (currentNode->getElement() != "XX") {
            return false;
        }
        currentNode = currentNode->getNext();
    }
    return true;
}

void Segment::clearSeats() {
    while (seats.getHead() != nullptr) {
        seats.deleteNode(0);
    }
}
