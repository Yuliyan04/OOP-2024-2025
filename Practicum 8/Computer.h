#pragma once
#include <iostream>


class Computer
{
	unsigned serialNumber;
	char* brand;
	char* processor;
	unsigned video;
	unsigned hd;
	unsigned weight;
	unsigned batteryLife;
	double price;
	unsigned quantity;

public:

	Computer();
	Computer(const Computer& other);
	Computer& operator=(const Computer& other);
	~Computer();

	void setQuantity(unsigned newQuan);

	unsigned getSerialNumber() const;
	const char* getBrand() const;
	const char* getProcessor() const;
	unsigned getVideo() const;
	unsigned getHD() const;
	unsigned getWeight() const;
	unsigned getBatteryLife() const;
	double getPrice() const;
	unsigned getQuantity() const;

	void print() const;

private:

	void copyFrom(const Computer& other);
	void free();
};

