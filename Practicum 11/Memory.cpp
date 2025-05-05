#include "Memory.h"


constexpr double pricePerGB = 89.99;

void Memory::setMemory(unsigned short mem)
{
	if (mem >= 1 && mem <= 10000)
	{
		capacity = mem;
		return;
	}
	throw std::invalid_argument("Memory is not in the right range...");
}

Memory::Memory() : Component(), capacity(1) {}

Memory::Memory(unsigned short capacity, const char* tag) : Component(tag)
{
	setMemory(capacity);
}


double Memory::price() const
{
	return capacity * pricePerGB;
}

void Memory::output(std::ostream& os) const
{
	os << tag << "\n";
	os << capacity << "\n";
	os << price() << "\n";
}


Component* Memory::clone() const
{
	return new Memory(*this);
}