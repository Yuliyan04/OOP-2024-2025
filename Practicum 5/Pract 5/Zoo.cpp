#include "Zoo.h"

void Zoo::copyFrom(const Zoo& other)
{
	zooName = new char[strlen(other.zooName) + 1];
	strcpy(zooName, other.zooName);

	capacity = other.capacity;
	count = other.count;

	animals = new Animal[capacity];

	for (size_t i = 0; i < count; i++)
	{
		animals[i] = other.animals[i];
	}
}

void Zoo::free()
{
	delete[] zooName;
	delete[] animals;

	zooName = nullptr;
	animals = nullptr;
	capacity = 0;
	count = 0;
}

Zoo::Zoo() :zooName(nullptr), animals(nullptr), capacity(0), count(0) {}

Zoo::Zoo(const Zoo& other) : Zoo()
{
	if (this != &other)
	{
		copyFrom(other);
	}
}

Zoo Zoo::operator=(const Zoo& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Zoo::~Zoo()
{
	free();
}

Zoo::Zoo(size_t cap) :Zoo()
{
	capacity = cap;
	animals = new Animal[cap];
}


int Zoo::getAnimalIndex(const char* name) const
{
	int idx = -1;

	if (!name)
	{
		return idx;
	}

	for (size_t i = 0; i < count; i++)
	{
		if (strcmp(name, animals[i].getName()) == 0)
		{
			return i;
		}
	}

	return idx;
}

void Zoo::addAnimal(const Animal& other)
{
	if (count >= capacity)
	{
		return;
	}

	animals[count] = other;
	count++;
}


void Zoo::removeAnimal(const char* name)
{
	if (!name) return;

	int idx = getAnimalIndex(name);
	if (idx == -1) return;

	for (size_t i = idx; i < count - 1; i++)
	{
		animals[i] = animals[i + 1];
	}
}

unsigned Zoo::getAnimalsByKind(Kind kind) const
{
	unsigned count = 0;
	for (size_t i = 0; i < count; i++)
	{
		if (animals[i].getKind() == kind) count++;
	}

	return count;
}


void Zoo::saveToFile(std::ostream& ofs) const
{
	ofs << "Animals: " << count << "/" << capacity << std::endl;
	ofs << "/Name, Kind, Age/" << std::endl;

	for (size_t i = 0; i < count; i++)
	{
		animals[i].saveAnimal(ofs);
	}
}

void Zoo::print() const
{
	saveToFile(std::cout);
}