#include "AirBnb.h"


unsigned getResizeValue(int num)
{
	unsigned res = 1;
	while (res <= num)
	{
		res = res << 1;
	}
	return std::max(res, 16u);
}

void AirBnb::copyFrom(const AirBnb& other)
{
	size = other.size;
	capacity = other.capacity;
	places = new Accomodation[capacity];
	for (size_t i = 0; i < size; i++)
	{
		places[i] = other.places[i];
	}
}

void AirBnb::free()
{
	delete[] places;
	places = nullptr;
	size = capacity = 0;
}

void AirBnb::resize(unsigned newCap)
{
	if (newCap < size)
	{
		return;
	}

	Accomodation* newPlaces = new Accomodation[newCap];
	for (size_t i = 0; i < size; i++)
	{
		newPlaces[i] = places[i];
	}
	capacity = newCap;
	delete[] places;
	places = newPlaces;
}


AirBnb::AirBnb() :places(nullptr), size(0), capacity(0) {}

AirBnb::AirBnb(const AirBnb& other)
{
	copyFrom(other);
}

AirBnb& AirBnb::operator=(const AirBnb& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

AirBnb::~AirBnb()
{
	free();
}

AirBnb::AirBnb(const Accomodation* places, size_t size)
{
	capacity = getResizeValue(size);
	this->places = new Accomodation[capacity];
	this->size = size;
	for (size_t i = 0; i < size; i++)
	{
		this->places[i] = places[i];
	}
}


void AirBnb::addNewPlace(const Accomodation& toAdd)
{
	if (size == capacity)
	{
		resize(capacity);
	}

	places[size] = toAdd;
	size++;
}

Accomodation& AirBnb::findByID(unsigned ID)
{
	for (size_t i = 0; i < size; i++)
	{
		if (places[i].getID() == ID)
		{
			return places[i];
		}
	}

	throw std::invalid_argument("This ID doesn't exist");
}

void AirBnb::reserve(unsigned ID, size_t period)
{
	try
	{
		findByID(ID);
	}
	catch (std::invalid_argument)
	{
		return;
	}

	findByID(ID).setResDays(period);
	findByID(ID).reserveAcc();
}

void AirBnb::unreserve(unsigned ID, size_t period)
{
	try
	{
		findByID(ID);
	}
	catch (std::invalid_argument)
	{
		return;
	}

	findByID(ID).setResDays(0);
	findByID(ID).removeReservation();
}

double AirBnb::getProfit() const
{
	double sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		if(places[i].isReserved())
			sum += places[i].getResDays() * places[i].getPrice();
	}
	return sum;
}

Accomodation& AirBnb::findByLocation(const Point& location) const
{
	unsigned residx = 0;
	double closest = 0;

	for (size_t i = 0; i < size; i++)
	{
		Point currLoc = places[i].getLocation();
		double x2 = (location.x - currLoc.x) * (location.x - currLoc.x);
		double y2 = (location.y - currLoc.y) * (location.y - currLoc.y);
		double currDist = sqrt(x2 + y2);
		if (currDist - closest < 0)
		{
			residx = i;
			closest = currDist;
		}
	}
	return places[residx];
}

void AirBnb::removeByID(unsigned ID)
{
	int idx = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (places[i].getID() == ID)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		throw std::invalid_argument("There is no place with such ID...");
	}

	size--;
	for (size_t i = idx; i < size; i++)
	{
		std::swap(places[i], places[i + 1]);
	}
	places[size + 1].~Accomodation();
}