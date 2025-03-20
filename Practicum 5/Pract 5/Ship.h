#pragma once
#include <cstring>


enum class ShipClass
{
	bb,
	bc,
	unknown
};


class Ship
{
	char* shipName;
	unsigned launchYear;
	ShipClass shipClass;
	unsigned gunsCount;

public:

	Ship(const char* name, unsigned year, ShipClass shipClass, unsigned gunsCount);

	Ship();
	Ship(const Ship& other);
	Ship& operator=(const Ship& other);
	~Ship();

	void setShipName(const char* name);
	void setLaunchYear(unsigned year);
	void setShipClass(ShipClass shipClass);
	void setGunsCount(unsigned gunsNum);

	const char* getShipName() const;
	unsigned getLaunchYear() const;
	ShipClass getShipClass() const;
	unsigned getGunsCount() const;

private:

	void copyFrom(const Ship& other);
	void free();
};