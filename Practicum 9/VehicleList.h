#pragma once
#include "Vehicle.h"

class VehicleList
{
	Vehicle** vehicles;
	size_t size;
	size_t capacity;
public:

	VehicleList();
	VehicleList(const VehicleList& other);
	VehicleList(VehicleList&& other) noexcept;
	VehicleList& operator=(const VehicleList& other);
	VehicleList& operator=(VehicleList&& other) noexcept;
	~VehicleList();

	VehicleList(size_t capacity);

	void addVehicle(const Vehicle& other);
	bool isEmpty() const;
	size_t getCapacity() const;
	size_t getSize() const;
	int searchByRegistration(const Vehicle& other) const;

	const Vehicle* operator[](size_t pos) const;
	Vehicle* operator[](size_t pos);

private:

	void copyFrom(const VehicleList& other);
	void moveFrom(VehicleList&& other);
	void free();
	void resize();
};