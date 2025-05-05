#pragma once
#include "Device.h"


class SmartLight : public Device
{
	unsigned brighLevel;

public:

	void turnOn() const override;
	void turnOff() const override;
	void printDetails() const override;
};

