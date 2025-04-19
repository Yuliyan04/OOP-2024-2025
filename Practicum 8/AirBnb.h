#pragma once
#include "Accomodation.h"

class AirBnb
{
	Accomodation* places;
	size_t size;
	size_t capacity;

public:

	AirBnb();
	AirBnb(const AirBnb& other);
	AirBnb& operator=(const AirBnb& other);
	~AirBnb();

	AirBnb(const Accomodation* places, size_t size);

	void addNewPlace(const Accomodation& toAdd);
	Accomodation& findByID(unsigned ID);
	Accomodation& findByLocation(const Point& location) const;
	void reserve(unsigned ID, size_t period);
	void unreserve(unsigned ID, size_t period);
	double getProfit() const;
	void removeByID(unsigned ID);

private:

	void copyFrom(const AirBnb& other);
	void free();
	void resize(unsigned newSize);
};

