#include "Ticket.h"


Ticket::Ticket() : production(""), price(0.0) {}

Ticket::Ticket(const char* production, double price)
{
	this->production = production;
	this->price = price;
}

void Ticket::print() const
{
	std::cout << production << std::endl;
	std::cout << price << std::endl;
}