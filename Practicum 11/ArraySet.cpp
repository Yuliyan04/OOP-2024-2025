#include "ArraySet.h"

void ArraySet::copyFrom(const ArraySet& other)
{
	size = other.size;
	set = new int[size];
	for (size_t i = 0; i < size; i++)
	{
		set[i] = other.set[i];
	}
}

void ArraySet::moveFrom(ArraySet&& other)
{
	size = other.size;
	set = other.set;
	other.set = nullptr;
}

void ArraySet::free()
{
	delete[] set;
	set = nullptr;
}


ArraySet::ArraySet() : IntSet(), set(nullptr), size(0) {}

ArraySet::ArraySet(const ArraySet* other) : IntSet()
{
	copyFrom(other);
}

ArraySet::ArraySet(ArraySet&& other) noexcept : IntSet()
{
	moveFrom(std::move(other));
}

ArraySet& ArraySet::operator=(const ArraySet& other)
{
	if (this != &other)
	{
		IntSet::operator=(other);
		free();
		copyFrom(other);
	}
	return *this;
}

ArraySet& ArraySet::operator=(ArraySet&& other) noexcept
{
	if (this != &other)
	{
		IntSet::operator=(std::move(other));
		free();
		moveFrom(std::move(other));
	}
	return *this;
}

ArraySet::~ArraySet()
{
	free();
}


ArraySet::ArraySet(size_t n) : IntSet()
{
	set = new int[n];
	size = n;
}


bool ArraySet::member(int x) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (set[i] == x)
		{
			return true;
		}
	}
	return false;
}

int ArraySet::get(int i) const
{
	if (i >= size)
	{
		throw std::invalid_argument("Index can't be bigger than size.");
	}

	return set[i];
}


bool ArraySet::isSubsetOf(const IntSet* other) const
{
	return other->isSubsetOfAS(this);
}

bool ArraySet::isSubsetOfAS(const ArraySet* other) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (!other->member(set[i]))
		{
			return false;
		}
	}
	return true;
}

bool ArraySet::isSubsetOfIR(const IntRange* other) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (!other->member(set[i]))
		{
			return false;
		}
	}
	return true;
}


bool ArraySet::intersectWith(const IntSet* other) const
{
	return other->intersectWithAS(this);
}

bool ArraySet::intersectWithAS(const ArraySet* other) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (other->member(set[i]))
		{
			return true;
		}
	}
	return false;
}

bool ArraySet::intersectWithIR(const IntRange* other) const
{
	for (size_t i = 0; i < size; i++)
	{
		if (other->member(set[i]))
		{
			return true;
		}
	}
	return false;
}