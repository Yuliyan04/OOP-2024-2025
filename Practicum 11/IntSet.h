#pragma once
#include <iostream>


class ArraySet;
class IntRange;


class IntSet
{
public:

	IntSet() = default;

	virtual bool member(int x) const = 0;
	virtual int get(int i) const = 0;

	virtual bool isSubsetOf(const IntSet* other) const = 0;
	virtual bool isSubsetOfAS(const ArraySet* other) const = 0;
	virtual bool isSubsetOfIR(const IntRange* other) const = 0;

	virtual bool intersectWith(const IntSet* other) const = 0;
	virtual bool intersectWithAS(const ArraySet* other) const = 0;
	virtual bool intersectWithIR(const IntRange* other) const = 0;

	virtual ~IntSet() = default;
};