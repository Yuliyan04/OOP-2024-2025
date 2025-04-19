#include "VehicleList.h"


void VehicleList::copyFrom(const VehicleList& other)
{
	capacity = other.capacity;
	size = other.size;

	vehicles = new Vehicle * [capacity] {nullptr};
	for (size_t i = 0; i < size; i++)
	{
		vehicles[i] = new Vehicle(*other.vehicles[i]);
	}
}

void VehicleList::moveFrom(VehicleList&& other)
{
	capacity = other.capacity;
	size = other.size;

	vehicles = other.vehicles;
	other.vehicles = nullptr;
}

void VehicleList::free()
{
	for (size_t i = 0; i < capacity; i++)
	{
		delete vehicles[i];
	}
	delete[] vehicles;
}

void VehicleList::resize()
{
	capacity *= 2;
	Vehicle** newVehicles = new Vehicle * [capacity] {nullptr};

	for (size_t i = 0; i < size; i++)
	{
		newVehicles[i] = vehicles[i];
		vehicles[i] = nullptr;
	}

	for (size_t i = 0; i < capacity / 2; i++)
	{
		delete vehicles[i];
	}
	delete[] vehicles;

	vehicles = newVehicles;
}


VehicleList::VehicleList() : vehicles(nullptr), capacity(0), size(0) {}

VehicleList::VehicleList(const VehicleList& other)
{
	copyFrom(other);
}

VehicleList::VehicleList(VehicleList&& other) noexcept
{
	moveFrom(std::move(other));
}

VehicleList& VehicleList::operator=(const VehicleList& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

VehicleList& VehicleList::operator=(VehicleList&& other) noexcept
{
	if (this != &other)
	{
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

VehicleList::~VehicleList()
{
	free();
}


VehicleList::VehicleList(size_t capacity)
{
	this->capacity = capacity;
	vehicles = new Vehicle * [capacity] {nullptr};
	size = 0;
}


void VehicleList::addVehicle(const Vehicle& toAdd)
{
	for (size_t i = 0; i < size; i++)
	{
		if (vehicles[i]->getRegistration() == toAdd.getRegistration())
		{
			throw std::invalid_argument("Vehicle registration already exists");
		}
	}

	if (size == capacity)
	{
		resize();
	}

	size_t pos = size;

	for (size_t i = 0; i < size; i++)
	{
		if (!vehicles[i])
		{
			pos = i;
			break;
		}
	}

	Vehicle* toAddPtr = new Vehicle(toAdd);
	vehicles[pos] = toAddPtr;

	if(pos == size) size++;
}

bool VehicleList::isEmpty() const
{
	return size == 0;
}

size_t VehicleList::getCapacity() const
{
	return capacity;
}

size_t VehicleList::getSize() const
{
	return size;
}

int VehicleList::searchByRegistration(const Vehicle& other) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (vehicles[i]->getRegistration() == other.getRegistration())
		{
			return i;
		}
	}

	return -1;
}


const Vehicle* VehicleList::operator[](size_t pos) const
{
	if (pos >= capacity)
	{
		throw std::out_of_range("The index is out of range");
	}
	return vehicles[pos];
}

Vehicle* VehicleList::operator[](size_t pos)
{
	if (pos >= capacity)
	{
		throw std::out_of_range("The index is out of range");
	}
	return vehicles[pos];
}