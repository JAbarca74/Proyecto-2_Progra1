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

void Segment::updateData(int numberSeatingRows_, int numberSeatingColumns_, float price_)
{
    numberSeatingRows = numberSeatingRows_;
    numberSeatingColumns = numberSeatingColumns_;
    price = price_;

    seats = new string * [numberSeatingRows];
    for (int letter = 0; letter < numberSeatingRows; letter++)
    {
        seats[letter] = new string[numberSeatingColumns];
        for (int number = 0; number < numberSeatingColumns; number++)
        {
            string seatLabel;
            if (letter < 26) {
                seatLabel = string(1, 'A' + letter);
            }
            else {
                char firstLetter = 'A' + (letter / 26) - 1;
                char secondLetter = 'A' + (letter % 26);
                seatLabel = string(1, firstLetter) + string(1, secondLetter);
            }
            seats[letter][number] = seatLabel + to_string(number + 1);
        }
    }
}

void Segment::printSeats() {
    for (int i = 0; i < numberSeatingRows; i++)
    {
        for (int j = 0; j < numberSeatingColumns; j++)
        {
            if (seats[i][j] != "XX")
            {
                cout << GREEN << "[ |_" << seats[i][j] << "_| ] " << RESET;
            }
            else {
                cout << RED << "[ |_" << seats[i][j] << "_| ] " << RESET;
            }
        }
        cout << endl;
    }
    cout << endl;
}

bool Segment::reserveSeat(string seatCode)
{
    for (int i = 0; i < numberSeatingRows; i++)
    {
        for (int j = 0; j < numberSeatingColumns; j++)
        {
            if (seats[i][j] == seatCode) {
                seats[i][j] = "XX";
                return true;
            }
        }
    }
    return false;
}

bool Segment::isFullTheEvent()
{
    for (int i = 0; i < numberSeatingRows; i++)
    {
        for (int j = 0; j < numberSeatingColumns; j++)
        {
            if (seats[i][j] != "XX")
            {
                return true;
            }
        }
    }
    return false;
}

void Segment::clearSeats()
{
    if (seats != nullptr)
    {
        for (int i = 0; i < numberSeatingRows; i++)
        {
            delete[] seats[i];
        }
        delete[] seats;
        seats = nullptr;
    }
}