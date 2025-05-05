#pragma once
#include "MyString.h"


class Device
{
protected:

	String name;
	double price;

public:

	Device() = default;

	virtual void turnOn() const = 0;
	virtual void turnOff() const = 0;
	virtual void printDetails() const = 0;

	virtual ~Device();
};