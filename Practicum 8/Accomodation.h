#pragma once
#include <iostream>


enum class AccomType
{
	Apartment,
	Hotel,
	Villa,
	Unknown
};


struct Point
{
	int x;
	int y;
};


class Accomodation
{
	unsigned ID;
	char* name;
	AccomType type;
	Point location;
	double pricePerNight;
	bool reserved;
	unsigned resDays;

public:

	Accomodation();
	Accomodation(const Accomodation& other);
	Accomodation& operator=(const Accomodation& other);
	~Accomodation();

	unsigned getID() const;
	const char* getName() const;
	AccomType getType() const;
	Point getLocation() const;
	double getPrice() const;
	bool isReserved() const;
	unsigned getResDays() const;

	double getWholeSum() const;

	void setID(unsigned newID);
	void setName(const char* newName);
	void setType(AccomType newType);
	void setLocation(Point& newLocation);
	void setPrice(double& newPrice);
	void setResDays(unsigned resDays);

	void reserveAcc();
	void removeReservation();

private:

	void copyFrom(const Accomodation& other);
	void free();
};

