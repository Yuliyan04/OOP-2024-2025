#pragma once
#include "IntSet.h"
#include "ArraySet.h"

class IntRange : public IntSet
{
	int beg;
	int end;

public:

	IntRange();
	IntRange(int a, int b);

	bool member(int x) const override;
	int get(int i) const const override;

	bool isSubsetOf(const IntSet* other) const override;
	bool isSubsetOfAS(const ArraySet* other) const override;
	bool isSubsetOfIR(const IntRange* other) const override;

	bool intersectWith(const IntSet* other) const override;
	bool intersectWithAS(const ArraySet* other) const override;
	bool intersectWithIR(const IntRange* other) const override;
};

