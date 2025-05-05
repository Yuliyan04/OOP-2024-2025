#pragma once
#include  "Component.h"


class Memory : public Component
{
	unsigned short capacity;

public:

	Memory();
	Memory(unsigned short capacity, const char* tag);

	double price() const override;
	void output(std::ostream& os) const override;

	Component* clone() const override;

private:

	void setMemory(unsigned short mem);
};

