#pragma once
#include "Ticket.h"


class GroupTicket : public Ticket
{
public:

	GroupTicket();
	GroupTicket(const char* name, double Price);
};

