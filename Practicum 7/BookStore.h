#pragma once
#include "Book.h"

class BookStore
{
	char* name;
	Book* books;
	size_t size;
	size_t capacity;

public:

	BookStore();
	BookStore(const BookStore& other);
	BookStore& operator=(const BookStore& other);
	~BookStore();

	void setName(const char* name);
	void setBooks(const Book* books, size_t capacity, size_t size);

	size_t getCapacity() const;
	size_t getSize() const;
	const Book* getBooks() const;
	const char* getName() const;

	BookStore& operator+=(const Book& toAdd);
	BookStore& operator-=(const Book& toRemove);

	void serializeBinary(std::ofstream& ofs);
	void deserializeBinary(std::ifstream& ifs);

private:

	void copyFrom(const BookStore& other);
	void free();
	void resize(unsigned toResize);
};

bool operator<(const BookStore& lhs, const BookStore& rhs);