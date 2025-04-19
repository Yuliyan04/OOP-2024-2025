#include "Computer.h"


void Computer::copyFrom(const Computer& other)
{
	serialNumber = other.serialNumber;

	brand = new char[strlen(other.brand) + 1];
	strcpy(brand, other.brand);

	processor = new char[strlen(other.processor) + 1];
	strcpy(processor, other.processor);

	video = other.video;
	hd = other.hd;
	weight = other.weight;
	batteryLife = other.batteryLife;
	price = other.price;
	quantity = other.quantity;
}

void Computer::free()
{
	delete[] brand, processor;
	brand = processor = nullptr;
	serialNumber = video = hd = weight = batteryLife = quantity = 0;
	price = 0;
}


Computer::Computer()
{
	brand = processor = nullptr;
	serialNumber = video = hd = weight = batteryLife = quantity = 0;
	price = 0;
}

Computer::Computer(const Computer& other)
{
	copyFrom(other);
}

Computer& Computer::operator=(const Computer& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Computer::~Computer()
{
	free();
}


void Computer::setQuantity(unsigned newQuan)
{
	if (quantity >= 0)
	{
		quantity = newQuan;
	}
}


unsigned Computer::getSerialNumber() const
{
	return serialNumber;
}

const char* Computer::getBrand() const
{
	return brand;
}

const char* Computer::getProcessor() const
{
	return processor;
}

unsigned Computer::getVideo() const
{
	return video;
}

unsigned Computer::getHD() const
{
	return hd;
}

unsigned Computer::getWeight() const
{
	return weight;
}

unsigned Computer::getBatteryLife() const
{
	return batteryLife;
}

double Computer::getPrice() const
{
	return price;
}

unsigned Computer::getQuantity() const
{
	return quantity;
}

void Computer::print() const
{
	std::cout << serialNumber << std::endl;
	std::cout << brand << std::endl;
	std::cout << processor << std::endl;
	std::cout << video << std::endl;
	std::cout << hd << std::endl;
	std::cout << weight << std::endl;
	std::cout << batteryLife << std::endl;
	std::cout << price << std::endl;
	std::cout << quantity << std::endl;
}