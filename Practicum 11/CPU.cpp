#include "CPU.h"


constexpr double pricePerCore = 29.99;

void CPU::setCores(unsigned short cores)
{
	if (cores >= 1 && cores <= 8)
	{
		this->cores = cores;
		return;
	}
	throw std::invalid_argument("Cores must be at least 1 and at most 8.");
}

CPU::CPU() : Component(), cores(1), MHz(0) {}

CPU::CPU(unsigned short cores, unsigned short MHz, const char* tag) : Component(tag)
{
	setCores(cores);
	this->MHz = MHz;
}


double CPU::price() const
{
	return cores * pricePerCore;
}

void CPU::output(std::ostream& os) const
{
	os << "tag" << "\n";
	os << MHz << ", " << "cores: " << cores << "\n";
	os << price() << "\n";
}


Component* CPU::clone() const
{
	return new CPU(*this);
}