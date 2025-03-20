#include "Ship.h"

void Ship::copyFrom(const Ship& other)
{
	shipName = new char[strlen(other.shipName) + 1];
	strcpy(shipName, other.shipName);

	shipClass = other.shipClass;
	launchYear = other.launchYear;
	gunsCount = other.gunsCount;
}

void Ship::free()
{
	delete[] shipName;

	shipName = nullptr;
	gunsCount = 0;
	launchYear = 0;
	shipClass = ShipClass::unknown;
}

void Ship::setShipName(const char* name)
{
	if (!name)
	{
		return;
	}

	delete[] shipName;
	shipName = new char[strlen(name) + 1];
	strcpy(shipName, name);
}

void Ship::setLaunchYear(unsigned year)
{
	if (year >= 0 && year <= 2025)
	{
		launchYear = year;
	}
}

void Ship::setShipClass(ShipClass toSet)
{
	if (toSet != ShipClass::unknown)
	{
		shipClass = toSet;
	}
}

void Ship::setGunsCount(unsigned guns)
{
	if (guns >= 0)
	{
		gunsCount = guns;
	}
}

Ship::Ship() : shipName(nullptr), launchYear(0), gunsCount(0), shipClass(ShipClass::unknown) {}

Ship::Ship(const Ship& other)
{
	copyFrom(other);
}

Ship& Ship::operator=(const Ship& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Ship::~Ship()
{
	free();
}

Ship::Ship(const char* name, unsigned year, ShipClass shipClass, unsigned gunsCount) :Ship()
{
	setShipName(name);
	setGunsCount(gunsCount);
	setLaunchYear(year);
	setShipClass(shipClass);
}

const char* Ship::getShipName() const
{
	return shipName;
}

unsigned Ship::getLaunchYear() const
{
	return launchYear;
}

ShipClass Ship::getShipClass() const
{
	return shipClass;
}

unsigned Ship::getGunsCount() const
{
	return gunsCount;
}