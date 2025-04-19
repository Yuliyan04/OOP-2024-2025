#pragma once
#include "Computer.h"
#include "Utility.h"


class ComputerStore
{
	char* name;
	Computer* computers;
	size_t size;
	size_t capacity;

public:

	ComputerStore();
	ComputerStore(const ComputerStore& other);
	ComputerStore& operator=(const ComputerStore& other);
	~ComputerStore();

	ComputerStore(const Computer* computers, size_t size, const char* name);

	void addComputer(const Computer& other);
	void print() const;
	void buy(const char* brand, double money);
	void printGamingANDTravel() const;

private:

	void copyFrom(const ComputerStore& other);
	void free();
	void resize();
};

