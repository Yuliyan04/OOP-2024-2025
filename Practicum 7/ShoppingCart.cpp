#include "ShoppingCart.h"


void ShoppingCart::copyFrom(const ShoppingCart& other)
{
	size = other.size;
	capacity = other.capacity;
	items = new Item[capacity];
	for (size_t i = 0; i < size; i++)
	{
		items[i] = other.items[i];
	}
}

void ShoppingCart::free()
{
	delete[] items;
	items = nullptr;
	size = 0;
	capacity = 0;
}

unsigned getClosestPower2(size_t strSize)
{
	unsigned size = 1;
	while (size < strSize)
	{
		size = size << 1;
	}
	return std::max(size, 16u);
}

void ShoppingCart::resize(unsigned n)
{
	if (n < size)
	{
		return;
	}

	Item* newItems = new Item[n];
	for (size_t i = 0; i < size; i++)
	{
		newItems[i] = items[i];
	}

	delete[] items;
	items = newItems;
	capacity = n;
}

ShoppingCart::ShoppingCart() :items(nullptr), size(0), capacity(0) {}

ShoppingCart::ShoppingCart(const ShoppingCart& other)
{
	copyFrom(other);
}

ShoppingCart& ShoppingCart::operator=(const ShoppingCart& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
}

ShoppingCart::~ShoppingCart()
{
	free();
}


void ShoppingCart::addItem(const Item& toAdd)
{
	for (size_t i = 0; i < size; i++)
	{
		if (items[i].getName() == toAdd.getName())
		{
			return;
		}
	}

	if (size == capacity)
	{
		resize(getClosestPower2(capacity));
	}

	items[size] = toAdd;
	size++;
}

void ShoppingCart::removeItem(const Item& toRem)
{
	int idx = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (items[i].getName() == toRem.getName())
		{
			idx = i;
		}
	}

	if (idx == -1)
	{
		return;
	}

	size--;
	for (size_t i = idx; i < size; i++)
	{
		std::swap(items[i], items[i + 1]);
	}
	items[size + 1].~Item();
}


unsigned ShoppingCart::itemsCount() const
{
	return size;
}

bool ShoppingCart::isEmpty() const
{
	return size == 0;
}

double ShoppingCart::getPriceOf(String& name) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (items[i].getName() == name)
		{
			return items[i].getPrice();
		}
	}

	return 0.0;
}

double ShoppingCart::getTotalPrice() const
{
	double sum = 0;
	for (size_t i = 0; i < size; i++)
	{
		sum += items[i].getPrice();
	}
	return sum;
}

void ShoppingCart::sortByNameLexic()
{

}


void ShoppingCart::serializeBinary(std::ofstream& ofs)
{
	ofs.write((const char*)&capacity, sizeof(capacity));
	ofs.write((const char*)&size, sizeof(size));

	for (size_t i = 0; i < size; i++)
	{
		items[i].serializeBinary(ofs);
	}
}


void ShoppingCart::deserializeBinary(std::ifstream& ifs)
{
	ifs.read((char*)&capacity, sizeof(capacity));
	ifs.read((char*)&size, sizeof(size));

	items = new Item[capacity];

	for (size_t i = 0; i < size; i++)
	{
		items[i].deserializeBinary(ifs);
	}
}