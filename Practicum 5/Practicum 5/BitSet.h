#pragma once
#include <iostream>

const size_t BUCKET_SIZE = 8;

class BitSet
{
	unsigned char* set;
	size_t setSize;

public:

	BitSet(unsigned n);

	BitSet();
	BitSet(const BitSet& other);
	BitSet& operator=(const BitSet& other);
	~BitSet();

	size_t getSetSize() const;

	void addNum(unsigned n);
	void removeNum(unsigned n);
	bool isInSet(unsigned n) const;
	void printSet() const;
	BitSet unite(const BitSet& other) const;
	BitSet intersect(const BitSet& other) const;

private:

	void copyFrom(const BitSet& other);
	void free();

	size_t getSetSize(unsigned n) const;
	void makeSet(unsigned n);

	size_t getBucket(unsigned n) const;
	size_t getBucketIndex(int n) const;
};