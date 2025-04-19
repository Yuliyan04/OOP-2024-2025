#include "ComputerStore.h"


void ComputerStore::copyFrom(const ComputerStore& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	capacity = other.capacity;
	size = other.size;

	computers = new Computer[capacity];
	for (size_t i = 0; i < size; i++)
	{
		computers[i] = other.computers[i];
	}
}

void ComputerStore::free()
{
	delete[] computers, name;
	computers = nullptr;
	name = nullptr;
	capacity = size = 0;
}

void ComputerStore::resize()
{ 
	capacity *= 2;
	Computer* newComps = new Computer[capacity];

	for (size_t i = 0; i < size; i++)
	{
		newComps[i] = computers[i];
	}

	delete[] computers;
	computers = newComps;
}


ComputerStore::ComputerStore() : name(nullptr), computers(nullptr), size(0), capacity(0) {}

ComputerStore::ComputerStore(const ComputerStore& other)
{
	copyFrom(other);
}

ComputerStore& ComputerStore::operator=(const ComputerStore& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return* this;
}

ComputerStore::~ComputerStore()
{
	free();
}

ComputerStore::ComputerStore(const Computer* computers, size_t size, const char* name)
{
	capacity = size * 2;
	this->size = size;

	this->computers = new Computer[capacity];
	for (size_t i = 0; i < size; i++)
	{
		this->computers[i] = computers[i];
	}

	this->name = new char[strlen(name) + 1];
	strcpy(this->name, name);
}


void ComputerStore::addComputer(const Computer& other)
{
	int idx = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (other.getBrand() == computers[i].getBrand())
		{
			idx = i;
		}
	}

	if (idx != -1)
	{
		computers[idx].setQuantity(computers[idx].getQuantity() + 1);
		return;
	}

	if (capacity == size)
	{
		resize();
	}

	computers[size] = other;
	size++;
}

void ComputerStore::print() const
{
	std::cout << name;
	for (size_t i = 0; i < size; i++)
	{
		computers[i].print();
	}
}

void ComputerStore::buy(const char* brand, double money)
{
	int idx = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (strcmp(computers[i].getBrand(), brand) == 0 && computers[i].getQuantity() > 0)
		{
			idx = i;
			break;
		}
	}

	if (idx == -1)
	{
		throw std::invalid_argument("There is no such brand in this store or it has been sold.");
	}

	if (computers[idx].getPrice() > money)
	{
		throw std::invalid_argument("Not enough money to buy this computer");
	}

	computers[idx].setQuantity(computers[idx].getQuantity() - 1);
}

void ComputerStore::printGamingANDTravel() const
{
	for (size_t i = 0; i < size; i++)
	{
		if (Utility::isGoodForGamng(computers[i]) || Utility::isGoodForTravel(computers[i]))
		{
			computers[i].print();
		}
	}
}