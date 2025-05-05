#pragma once
#include "IntSet.h"
#include "IntRange.h"


class ArraySet : IntSet
{
	int* set;
	size_t size;

public:

	ArraySet();
	ArraySet(const ArraySet* other);
	ArraySet(ArraySet&& other) noexcept;
	ArraySet& operator=(const ArraySet& other);
	ArraySet& operator=(ArraySet&& other) noexcept;
	ArraySet();

	ArraySet(size_t n);

	bool member(int x) const override;
	int get(int i) const override;

	bool isSubsetOf(const IntSet* other) const override;
	bool isSubsetOfAS(const ArraySet* other) const override;
	bool isSubsetOfIR(const IntRange* other) const override;

	bool intersectWith(const IntSet* other) const override;
	bool intersectWithAS(const ArraySet* other) const override;
	bool intersectWithIR(const IntRange* other) const override;

private:

	void copyFrom(const ArraySet& other);
	void moveFrom(ArraySet&& other);
	void free();
};

