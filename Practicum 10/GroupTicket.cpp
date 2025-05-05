#include "GroupTicket.h"


GroupTicket::GroupTicket() : Ticket() {}

GroupTicket::GroupTicket(const char* name, double Price) : Ticket(name, Price * 0.2) {}