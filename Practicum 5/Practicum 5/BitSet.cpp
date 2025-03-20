#include "BitSet.h"



void BitSet::copyFrom(const BitSet& other)
{
	setSize = other.setSize;
	set = new unsigned char[setSize];

	for (size_t i = 0; i < setSize; i++)
	{
		set[i] = other.set[i];
	}
}

void BitSet::free()
{
	delete[] set;
	set = nullptr;
	setSize = 0;
}

BitSet::BitSet() :set(nullptr), setSize(0) {}

BitSet::BitSet(const BitSet& other)
{
	copyFrom(other);
}

BitSet& BitSet::operator=(const BitSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}

	return *this;
}

BitSet::~BitSet()
{
	free();
}

size_t BitSet::getSetSize(unsigned n) const
{
	if (n % BUCKET_SIZE == 0)
	{
		return n / BUCKET_SIZE;
	}
	else
	{
		return (n / BUCKET_SIZE) + 1;
	}
}

void BitSet::makeSet(unsigned n)
{
	setSize = getSetSize(n);
	set = new unsigned char[setSize];

	for (size_t i = 0; i < setSize; i++)
	{
		set[i] = 0;
	}
}

BitSet::BitSet(unsigned n)
{
	makeSet(n);
}

size_t BitSet::getSetSize() const
{
	return setSize;
}

size_t BitSet::getBucket(unsigned n) const
{
	return n / BUCKET_SIZE;
}

size_t BitSet::getBucketIndex(int n) const
{
	return n % BUCKET_SIZE;
}


void BitSet::addNum(unsigned n)
{
	size_t bucket = getBucket(n);
	if (bucket >= setSize) return;

	size_t bucketIndex = getBucketIndex(n);

	unsigned char mask = 1;
	mask = mask << (BUCKET_SIZE - 1 - bucketIndex);

	set[bucket] |= mask;
}

void BitSet::removeNum(unsigned n)
{
	size_t bucket = getBucket(n);
	if (bucket >= setSize) return;

	size_t bucketIndex = getBucketIndex(n);

	unsigned char mask = 1;
	mask = mask << (BUCKET_SIZE - 1 - bucketIndex);
	mask = ~mask;

	set[bucket] &= mask;
}

bool BitSet::isInSet(unsigned n) const
{
	size_t bucket = getBucket(n);
	if (bucket >= setSize) return;

	size_t bucketIndex = getBucketIndex(n);

	unsigned char mask = 1;
	mask = mask << (BUCKET_SIZE - 1 - bucketIndex); 
	mask = mask & set[bucket];

	return mask != 0;
}

void BitSet::printSet() const
{
	if (setSize == 0)
	{
		std::cout << "{}" << std::endl;
		return;
	}

	unsigned lastNum = setSize * BUCKET_SIZE - 1;

	std::cout << "{ ";
	for (size_t i = 0; i <= lastNum; i++)
	{
		if (isInSet(i))
		{
			std::cout << i << " ";
		}
	}
	std::cout << "}" << std::endl;
}


BitSet BitSet::unite(const BitSet& other) const
{
	size_t resSize = std::max(setSize, other.setSize);
	BitSet res(resSize * BUCKET_SIZE);

	for (size_t i = 0; i < setSize; i++)
	{
		res.set[i] = res.set[i] | set[i];
	}

	for (size_t i = 0; i < other.getSetSize(); i++)
	{
		res.set[i] = res.set[i] | other.set[i];
	}
	
	return res;
}

BitSet BitSet::intersect(const BitSet& other) const
{
	size_t resSize = std::min(setSize, other.setSize);
	BitSet res(resSize * BUCKET_SIZE);

	for (size_t i = 0; i < resSize; i++)
	{
		res.set[i] = set[i] & other.set[i]; 
	}

	return res;
}