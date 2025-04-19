#include "Vehicle.h"


void Vehicle::copyFrom(const Vehicle& other)
{
	registration = other.registration;
	description = new char[strlen(other.description) + 1];
	strcpy(description, other.description);
}

void Vehicle::moveFrom(Vehicle&& other)
{
	description = other.description;
	other.description = nullptr;
	registration = std::move(other.registration);
}

void Vehicle::free()
{
	delete[] description;
}


Vehicle::Vehicle(const Vehicle& other) : registration(other.registration)
{
	copyFrom(other);
}

Vehicle::Vehicle(Vehicle&& other) : registration(std::move(other.registration))
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


Vehicle::Vehicle(const Registration& registration, const char* description) : registration(registration)
{
	if (!description)
	{
		throw std::invalid_argument("Description can't be nullptr");
	}

	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
}

Vehicle::Vehicle(Registration&& registration, const char* description) : registration(std::move(registration)) 
{
	if (!description)
	{
		throw std::invalid_argument("Description can't be nullptr");
	}

	this->description = new char[strlen(description) + 1];
	strcpy(this->description, description);
}


Registration Vehicle::getRegistration() const
{
	return registration;
}

const char* Vehicle::getDescription() const
{
	return description;
}