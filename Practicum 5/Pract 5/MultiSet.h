#pragma once
#include <iostream>

const size_t BUCKET_SIZE = 4;


class MultiSet
{
	unsigned char* multiSet;
	size_t multiSetSize;

public:
	
	MultiSet(unsigned n);

	MultiSet();
	MultiSet(const MultiSet& other);
	MultiSet& operator=(const MultiSet& other);
	~MultiSet();

	size_t getMultiSetSize() const;

	void add(unsigned n);
	void remove(unsigned n);
	size_t occurs(unsigned n) const;
	void print() const;
	MultiSet intersect(const MultiSet& other) const;

private:

	void copyFrom(const MultiSet& other);
	void free();

	size_t getMultiSetSize(unsigned n) const;
	void makeMultiSet(unsigned n);

	size_t getBucket(unsigned n) const;
	size_t getBucketIndex(unsigned n) const;
	size_t getShiftAmount(int n) const;
};

