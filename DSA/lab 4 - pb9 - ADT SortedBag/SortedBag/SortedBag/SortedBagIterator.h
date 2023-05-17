#pragma once
#include "SortedBag.h"

class SortedBag;

class SortedBagIterator
{
	friend class SortedBag;

private:
	const SortedBag& bag;
	SortedBagIterator(const SortedBag& b);

	//TODO - Representation
	int current;
	TComp* sortedElements;
	int sortedSize;

public:
	TComp getCurrent();
	bool valid();
	void next();
	void first();
};

