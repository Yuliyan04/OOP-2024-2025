#pragma once
#include "Ticket.h"

class StudentTicket : protected Ticket
{
public:

	StudentTicket();
	StudentTicket(const char* name, double originalPrice);
};

