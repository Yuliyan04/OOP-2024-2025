#include "Vehicle.h"


void Vehicle::copyFrom(const Vehicle& other)
{
	registration = new Registration(other.registration->getNumber());
	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);
}

void Vehicle::moveFrom(Vehicle&& other)
{
	description = other.description;
	other.description = nullptr;
	registration = other.registration;
	other.registration = nullptr;
}

void Vehicle::free()
{
	delete[] description, registration;
}


Vehicle::Vehicle(const Vehicle& other)
{
	copyFrom(other);
}

Vehicle::Vehicle(Vehicle&& other)
{
	moveFrom(std::move(other));
}

Vehicle& Vehicle::operator=(const Vehicle& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Vehicle& Vehicle::operator=(Vehicle&& other)
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
}

Vehicle::~Vehicle()
{
	free();
}


Vehicle::Vehicle(const Registration& registration, const char* description)
{
	if (!description)
	{
		throw std::invalid_argument("Description can't be nullptr");
	}

	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);

	this->registration = new Registration(registration.getNumber());
}


const Registration Vehicle::getRegistration() const
{
	return *registration;
}

const char* Vehicle::getDescription() const
{
	return description;
}