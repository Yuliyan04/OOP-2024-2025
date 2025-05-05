#pragma once
#include "MyString.h"


class Ticket
{
protected:

	MyString production;
	double price;

public:

	Ticket();
	Ticket(const char* production, double price);
	void print() const;
};