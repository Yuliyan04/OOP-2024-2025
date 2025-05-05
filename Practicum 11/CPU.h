#pragma once
#include  "Component.h"


class CPU : public Component
{
	unsigned short cores;
	unsigned short MHz;

public:

	CPU();
	CPU(unsigned short cores, unsigned short MHz, const char* tag);

	double price() const override;
	void output(std::ostream& os) const override;

	Component* clone() const override;

private:

	void setCores(unsigned short cores);
};

