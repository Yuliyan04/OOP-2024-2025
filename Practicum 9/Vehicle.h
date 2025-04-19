#pragma once
#include "Registration.h"

class Vehicle
{
	Registration registration;
	char* description;

public:

	Vehicle(const Vehicle& other);
	Vehicle(Vehicle&& other) noexcept;
	Vehicle& operator=(const Vehicle& other);
	Vehicle& operator=(Vehicle&& other) noexcept;
	~Vehicle();

	Vehicle(const Registration& registration, const char* description);
	Vehicle(Registration&& registration, const char* description);

	Registration getRegistration() const;
	const char* getDescription() const;

private:

	void copyFrom(const Vehicle& other);
	void moveFrom(Vehicle&& other);
	void free();
};

