#pragma once
#include "Item.h"

class ShoppingCart
{
	Item* items;
	size_t size;
	size_t capacity;

public:

	ShoppingCart();
	ShoppingCart(const ShoppingCart& other);
	ShoppingCart& operator=(const ShoppingCart& other);
	~ShoppingCart();

	void addItem(const Item& toAdd);
	void removeItem(const Item& toRem);

	unsigned itemsCount() const;
	bool isEmpty() const;
	double getPriceOf(String& name) const;
	double getTotalPrice() const;

	void sortByNameLexic();

	void serializeBinary(std::ofstream& ofs);
	void deserializeBinary(std::ifstream& ifs);

private:

	void copyFrom(const ShoppingCart& other);
	void free();
	void resize(unsigned n);
};

