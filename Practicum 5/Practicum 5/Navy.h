#pragma once
#include "Ship.h"

const size_t SHIPS_MAX_COUNT = 30;

class Navy
{
	char* country;
	Ship ships[SHIPS_MAX_COUNT];
	unsigned shipsCount;

public:

	Navy();
	Navy(const Navy& other);
	Navy& operator=(const Navy& other);
	~Navy();

	void addShip(const Ship& toAdd);
	void removeShipByName(const char* name);

	const Ship& at(unsigned ind) const;
	unsigned getShipsCount() const;
	int compare(const Navy& other) const;

	void setShips(const Ship* ships, unsigned count);
	void setCountry(const char* country);

private:

	void copyFrom(const Navy& other);
	void free();
};

