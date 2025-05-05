#include "IntRange.h"


IntRange::IntRange() : IntSet(), beg(0), end(0) {}

IntRange::IntRange(int a, int b) : IntSet(), beg(a), end(b) {}

bool IntRange::member(int x) const
{
	if (x >= beg && x <= end)
	{
		return true;
	}
	return false;
}

int IntRange::get(int i) const const
{
	if(i > end - beg + 1)
	return beg + i;
}

bool IntRange::isSubsetOf(const IntSet* other) const
{
	return other->isSubsetOfIR(this);
}

bool IntRange::isSubsetOfAS(const ArraySet* other) const
{
	for (size_t i = beg; i <= end; i++)
	{
		if (!other->member(i))
		{
			return false;
		}
	}
	return true;
}

bool IntRange::isSubsetOfIR(const IntRange* other) const
{
	for (size_t i = beg; i <= end; i++)
	{
		if (!other->member(i))
		{
			return false;
		}
	}
	return true;
}


bool IntRange::intersectWith(const IntSet* other) const
{
	return other->intersectWithIR(this);
}

bool IntRange::intersectWithAS(const ArraySet* other) const
{
	for (size_t i = beg; i <= end; i++)
	{
		if (other->member(i))
		{
			return true;
		}
	}
	return false;
}

bool IntRange::intersectWithIR(const IntRange* other) const
{
	for (size_t i = beg; i <= end; i++)
	{
		if (other->member(i))
		{
			return true;
		}
	}
	return false;
}