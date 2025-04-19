#include "Accomodation.h"


void Accomodation::copyFrom(const Accomodation& other)
{
	ID = other.ID;
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);
	type = other.type;
	location = other.location;
	pricePerNight = other.pricePerNight;
	reserved = other.reserved;
	resDays = other.resDays;
}

void Accomodation::free()
{
	delete[] name;
	name = nullptr;
	ID = 0;
	type = AccomType::Unknown;
	location = { 0,0 };
	pricePerNight = 0;
	reserved = false;
	resDays = 0;
}


Accomodation::Accomodation()
{
	name = nullptr;
	type = AccomType::Unknown;
	ID = 0;
	location = { 0,0 };
	pricePerNight = 0;
	reserved = false;
	resDays = 0;
}

Accomodation::Accomodation(const Accomodation& other)
{
	copyFrom(other);
}

Accomodation& Accomodation::operator=(const Accomodation& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Accomodation::~Accomodation()
{
	free();
}


unsigned Accomodation::getID() const
{
	return ID;
}

const char* Accomodation::getName() const
{
	return name;
}

AccomType Accomodation::getType() const
{
	return type;
}

Point Accomodation::getLocation() const
{
	return location;
}

double Accomodation::getPrice() const
{
	return pricePerNight;
}

bool Accomodation::isReserved() const
{
	return reserved;
}

unsigned Accomodation::getResDays() const
{
	return resDays;
}


void Accomodation::setID(unsigned newID)
{
	if (ID > 0)
	{
		ID = newID;
	}
}

void Accomodation::setName(const char* newName)
{
	if (newName)
	{
		delete[] name;
		name = new char[strlen(newName) + 1];
		strcpy(name, newName);
	}
	return;
}

void Accomodation::setType(AccomType newType)
{
	if (newType != AccomType::Unknown)
	{
		type = newType;
	}
}

void Accomodation::setLocation(Point& newLocation)
{
	location = newLocation;
}

void Accomodation::setPrice(double& newPrice)
{
	if (newPrice > 0)
	{
		pricePerNight = newPrice;
	}
}


void Accomodation::setResDays(unsigned resDays)
{
	if (resDays > 0)
	{
		this->resDays = resDays;
	}
}


double Accomodation::getWholeSum() const
{
	return pricePerNight * resDays;
}


void Accomodation::reserveAcc()
{
	if (reserved)
	{
		std::cout << "Place is already reserved";
		return;
	}
	reserved = true;
}

void Accomodation::removeReservation()
{
	reserved = false;
}