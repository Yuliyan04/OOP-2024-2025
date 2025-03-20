#include "Navy.h"

void Navy::setShips(const Ship* ships, unsigned count)
{
	if (!ships || count > SHIPS_MAX_COUNT)
	{
		return;
	}

	shipsCount = count;
	for (size_t i = 0; i < count; i++)
	{
		this->ships[i] = ships[i];
	}
}

void Navy::setCountry(const char* country)
{
	if (!country)
	{
		return;
	}

	delete[] this->country;
	this->country = new char[strlen(country) + 1];
	strcpy(this->country, country);
}

void Navy::copyFrom(const Navy& other)
{
	shipsCount = other.shipsCount;

	for (size_t i = 0; i < shipsCount; i++)
	{
		ships[i] = other.ships[i];
	}

	country = new char[strlen(other.country) + 1];
	strcpy(country, other.country);
}

void Navy::free()
{
	delete[] country;
	country = nullptr;
}


Navy::Navy() :shipsCount(0), country(nullptr) {}

Navy::Navy(const Navy& other)
{
	copyFrom(other);
}

Navy& Navy::operator=(const Navy& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Navy::~Navy()
{
	free();
}

const Ship& Navy::at(unsigned idx) const
{
	if (idx >= shipsCount)
	{
		return {};
	}

	return ships[idx];
}

unsigned Navy::getShipsCount() const
{
	return shipsCount;
}

int Navy::compare(const Navy& other) const
{
	unsigned currCount = 0;
	unsigned otherCount = 0;

	for (size_t i = 0; i < shipsCount; i++)
	{
		currCount += ships[i].getGunsCount();
	}

	for (size_t i = 0; i < other.shipsCount; i++)
	{
		otherCount += other.ships[i].getGunsCount();
	}

	if (currCount < otherCount)
	{
		return -1;
	}
	else if (currCount == otherCount)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

void Navy::addShip(const Ship& toAdd)
{
	if (shipsCount >= SHIPS_MAX_COUNT)
	{
		return;
	}

	ships[shipsCount] = toAdd;
	shipsCount++;
}

void Navy::removeShipByName(const char* name)
{
	int idx = -1;
	for (size_t i = 0; i < shipsCount; i++)
	{
		if (strcmp(name, ships[i].getShipName()) == 0)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		return;
	}

	for (size_t i = idx; i < shipsCount - 1; i++)
	{
		ships[i] = ships[i + 1];
	}
	shipsCount--;
}
