#include "StudentTicket.h"

StudentTicket::StudentTicket() : Ticket() {}

StudentTicket::StudentTicket(const char* name, double originalPrice) : Ticket(name, originalPrice * 0.5) {}