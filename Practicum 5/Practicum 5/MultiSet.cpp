#include "MultiSet.h"


void MultiSet::copyFrom(const MultiSet& other)
{
	multiSetSize = other.multiSetSize;
	multiSet = new unsigned char[multiSetSize];

	for (size_t i = 0; i < multiSetSize; i++)
	{
		multiSet[i] = other.multiSet[i];
	}
}

void MultiSet::free()
{
	delete[] multiSet;
	multiSet = nullptr;
	multiSetSize = 0;
}



MultiSet::MultiSet() :multiSet(nullptr), multiSetSize(0) {}

MultiSet::MultiSet(const MultiSet& other) : MultiSet()
{
	if (this != &other)
	{
		copyFrom(other);
	}
}

MultiSet& MultiSet::operator=(const MultiSet& other)
{
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

MultiSet::~MultiSet()
{
	free();
}



size_t MultiSet::getMultiSetSize(unsigned n) const
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

void MultiSet::makeMultiSet(unsigned n)
{
	multiSetSize = getMultiSetSize(n);
	multiSet = new unsigned char[multiSetSize];

	for (size_t i = 0; i < multiSetSize; i++)
	{
		multiSet[i] = 0;
	}
}


MultiSet::MultiSet(unsigned n)
{
	makeMultiSet(n);
}


size_t MultiSet::getMultiSetSize() const
{
	return multiSetSize;
}


size_t MultiSet::getBucket(unsigned n) const
{
	return n / BUCKET_SIZE;
}

size_t MultiSet::getBucketIndex(unsigned n) const
{
	return n % BUCKET_SIZE;
}

size_t MultiSet::getShiftAmount(int n) const
{
	size_t bucket = getBucket(n);
	size_t bucketIndex = getBucketIndex(n);

	return (BUCKET_SIZE - 1 - bucketIndex) + 2;;
}


size_t MultiSet::occurs(unsigned n) const
{
	size_t bucket = getBucket(n);
	size_t bucketIndex = getBucketIndex(n);

	int shiftAmount = (BUCKET_SIZE - 1 - bucketIndex) + 2;
	int mask = 3;
	mask = mask << shiftAmount;

	int count = mask & multiSet[bucket];
	count = count >> shiftAmount;

	return count;
}

void MultiSet::add(unsigned n)
{
	unsigned count = occurs(n);

	if (count == 3)
	{
		return; //more than 3
	}

	size_t shiftAmount = getShiftAmount(n);
	size_t bucket = getBucket(n);
	size_t bucketIndex = getBucketIndex(n);

	int mask = 3 << shiftAmount;

	count++;
	count = count << shiftAmount;

	multiSet[bucket] &= (~mask);
	multiSet[bucket] |= count;
}

void MultiSet::remove(unsigned n)
{
	unsigned count = occurs(n);

	if (count == 0)
	{
		return;
	}

	size_t shiftAmount = getShiftAmount(n);
	size_t bucket = getBucket(n);
	size_t bucketIndex = getBucketIndex(n);

	int mask = 3 << shiftAmount;

	count--;
	count = count << shiftAmount;

	multiSet[bucket] &= (~mask);
	multiSet[bucket] |= count;
}


void MultiSet::print() const
{
	unsigned lastNum = multiSetSize * BUCKET_SIZE - 1;

	std::cout << "{ ";
	for (size_t i = 0; i <= lastNum ; i++)
	{
		size_t count = occurs(i);
		for (size_t j = 0; j < count; j++)
		{
			std::cout << i << " ";
		}
	}
	std::cout << "}";
}

MultiSet MultiSet::intersect(const MultiSet& other) const
{
	size_t resSize = std::min(multiSetSize, other.multiSetSize);
	MultiSet res(resSize * BUCKET_SIZE);

	for (size_t i = 0; i < resSize; i++)
	{
		res.multiSet[i] = multiSet[i] & other.multiSet[i];
	}

	return res;
}