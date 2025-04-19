#pragma once
#include "String.h"

class Item
{
	String name;
	bool available;
	double price;

public:

	void serializeBinary(std::ofstream& ofs);
	void deserializeBinary(std::ifstream& ifs);

	Item(String name, double price);
	Item();
	~Item();

	String getName() const;
	double getPrice() const;

	void changeAvailability();
};

