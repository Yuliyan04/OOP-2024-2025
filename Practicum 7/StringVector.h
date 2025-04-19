#pragma once
#include "String.h"

class StringVector
{
	String* collection;
	size_t size;
	size_t capacity;
public:

	StringVector();
	StringVector(const StringVector& other);
	StringVector& operator=(const StringVector& other);
	~StringVector();

	void push_back(const String& toPush);
	void pop_back(const String& toPop);
	void insert(const String& toInsert, size_t pos);
	void erase(const String& toErase, size_t pos);
	void clear();

	unsigned getSize() const;
	bool empty() const;

	const String& operator[](size_t pos) const;
	String& operator[](size_t pos);

private:

	void copyFrom(const StringVector& other);
	void free();
	void resize(unsigned num);
};

