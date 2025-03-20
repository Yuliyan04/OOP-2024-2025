#pragma once
#include "Animal.h"
#include <fstream>
#include <iostream>

class Zoo
{
	char* zooName;
	Animal* animals;
	size_t capacity;
	size_t count = 0;

public:

	Zoo(size_t cap);

	Zoo();
	Zoo(const Zoo& other);
	Zoo operator=(const Zoo& other);
	~Zoo();

	void addAnimal(const Animal& other);
	void removeAnimal(const char* name);
	unsigned getAnimalsByKind(Kind kin) const;
	void print() const;
	void saveToFile(std::ostream& ofs) const;

private:

	void copyFrom(const Zoo& other);
	void free();

	int getAnimalIndex(const char* name) const;
};

