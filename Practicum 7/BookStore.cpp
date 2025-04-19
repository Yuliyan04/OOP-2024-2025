#include "BookStore.h"


void BookStore::copyFrom(const BookStore& other)
{
	name = new char[strlen(other.name) + 1];
	strcpy(name, other.name);

	books = new Book[other.capacity];
	size = other.size;
	for (size_t i = 0; i < size; i++)
	{
		books[i] = other.books[i];
	}
}

void BookStore::free()
{
	delete[] name, books;
	books = nullptr;
	name = nullptr;

	capacity = 0;
	size = 0;
}

void BookStore::resize(unsigned toResize)
{
	if (toResize < size)
	{
		return;
	}

	capacity = toResize;
	Book* newBooks = new Book[capacity];
	for (size_t i = 0; i < size; i++)
	{
		newBooks[i] = books[i];
	}

	delete[] books;
	books = newBooks;
}


BookStore::BookStore() :books(nullptr), name(nullptr), capacity(0), size(0) {}

BookStore::BookStore(const BookStore& other)
{
	copyFrom(other);
}

BookStore& BookStore::operator=(const BookStore& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

BookStore::~BookStore()
{
	free();
}


void BookStore::setName(const char* newName)
{
	if (!name)
	{
		return;
	}

	delete[] name;
	name = new char[strlen(newName) + 1];
	strcpy(name, newName);
}

void BookStore::setBooks(const Book* newBooks, size_t capacity, size_t size)
{
	if (!books || capacity < size)
	{
		return;
	}

	Book* newBookscpy = new Book[capacity];
	for (size_t i = 0; i < size; i++)
	{
		newBookscpy[i] = newBooks[i];
	}

	delete[] books;
	books = newBookscpy;
	this->capacity = capacity;
	this->size = size;
}

size_t BookStore::getCapacity() const
{
	return capacity;
}

size_t BookStore::getSize() const
{
	return size;
}

const Book* BookStore::getBooks() const
{
	return books;
}

const char* BookStore::getName() const
{
	return name;
}


unsigned getNextPower2(unsigned num)
{
	unsigned res = 1;
	while (res < num)
	{
		res = res << 1;
	}
	return res;
}

BookStore& BookStore::operator+=(const Book& toAdd)
{
	if (size == capacity)
	{
		resize(getNextPower2(capacity));
	}
	books[size] = toAdd;
	size++;
	return *this;
}

BookStore& BookStore::operator-=(const Book& toRemove)
{
	if (size == 0)
	{
		return;
	}

	int bookidx = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (toRemove.getID() == books[i].getID())
		{
			bookidx = i;
			break;
		}
	}

	if (bookidx < 0)
	{
		return;
	}

	size--;
	for (size_t i = bookidx; i < size; i++)
	{
		std::swap(books[i], books[i + 1]);
	}
	books[size + 1].~Book();

	return *this;
}

bool operator<(const BookStore& lhs, const BookStore& rhs)
{
	double lhsSum = 0;
	double rhsSum = 0;

	for (size_t i = 0; i < lhs.getSize(); i++)
	{
		lhsSum += lhs.getBooks()[i].gedPrice();
	}

	for (size_t i = 0; i < rhs.getSize(); i++)
	{
		rhsSum += rhs.getBooks()[i].gedPrice();
	}

	return lhsSum - rhsSum < 0;
}


void BookStore::serializeBinary(std::ofstream& ofs)
{
	size_t nameLen = strlen(name);
	ofs.write((const char*)&nameLen, sizeof(nameLen));
	ofs.write((const char*)name, sizeof(char) * nameLen);

	ofs.write((const char*)&capacity, sizeof(capacity));
	ofs.write((const char*)&size, sizeof(size));
	for (size_t i = 0; i < size; i++)
	{
		books[i].writeToBinaryFile(ofs);
	}
}

void BookStore::deserializeBinary(std::ifstream& ifs)
{
	size_t nameLen;
	ifs.read((char*)&nameLen, sizeof(nameLen));
	name = new char[nameLen + 1];
	name[nameLen] = '\0';
	ifs.read((char*)&name, sizeof(char) * nameLen);

	ifs.read((char*)&capacity, sizeof(capacity));
	ifs.read((char*)&size, sizeof(size));

	books = new Book[capacity];
	for (size_t i = 0; i < size; i++)
	{
		books[i].readFromBinaryFile(ifs);
	}
}