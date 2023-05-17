#include "SortedBagIterator.h"
#include "SortedBag.h"
#include <exception>

using namespace std;

SortedBagIterator::SortedBagIterator(const SortedBag& b) : bag(b) {
	//TODO - Implementation
	this->current = 0;

	// Create a sorted array of elements for iterating
	this->sortedSize = b.size();
	this->sortedElements = new TComp[this->sortedSize];
	int index = 0;
	for (int i = 0; i < b.capacity; i++) {
		if (b.counters[i] != 0) {
			for (int j = 0; j < b.counters[i]; j++) {
				this->sortedElements[index] = b.elements[i];
				index++;
			}
		}
	}
}

TComp SortedBagIterator::getCurrent() {
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	return this->sortedElements[this->current];
}

bool SortedBagIterator::valid() {
	//TODO - Implementation
	return this->current < this->sortedSize;
}

void SortedBagIterator::next() {
	//TODO - Implementation
	if (!this->valid()) {
		throw std::exception();
	}
	this->current++;
}

void SortedBagIterator::first() {
	//TODO - Implementation
	this->current = 0;
}

