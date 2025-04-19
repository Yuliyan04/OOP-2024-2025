#include "Item.h"


void Item::serializeBinary(std::ofstream& ofs)
{
	ofs.write((const char*)&available, sizeof(available));
	ofs.write((const char*)&price, sizeof(price));

	unsigned stringSize = name.getSize();
	ofs.write((const char*)&stringSize, sizeof(stringSize));
	ofs.write((const char*)name.c_str(), sizeof(char) * stringSize);
}

void Item::deserializeBinary(std::ifstream& ifs)
{
	ifs.read((char*)&available, sizeof(available));
	ifs.read((char*)&price, sizeof(price));

	unsigned strSize;
	ifs.read((char*)&strSize, sizeof(strSize));
	char* str = new char[strSize + 1];
	str[strSize] = '\0';
	ifs.read(str, sizeof(char) * strSize);

	String string(str);
	name = string;
}


String Item::getName() const
{
	return name;
}

double Item::getPrice() const
{
	return price;
}


Item::~Item()
{
	name.~String();
	price = 0;
	available = false;
}

Item::Item(String name, double price)
{
	this->name = name;
	this->price = price;
	available = true;
}

Item::Item() : available(false), name(""), price(0.0) {}


void Item::changeAvailability()
{
	available = !available;
}