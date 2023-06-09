#include "SortedSetIterator.h"
#include <exception>

using namespace std;

SortedSetIterator::SortedSetIterator(const SortedSet& m) : multime(m)
{
	// Constructor
	// Initialize the iterator by calling the 'first' function
	this->first();
}

void SortedSetIterator::first() {
	// Set the iterator to the first element in the sorted set
	this->position = this->multime.rootPosition;

	if (this->position == NONEXISTENT_POSITION) {
		// If the set is empty, make the position invalid
		this->position = this->multime.arrayCapacity;
		return;
	}

	// Find the position of the minimum element in the set
	this->position = this->multime.getPositionOfMinimum(this->position);
}

void SortedSetIterator::next() {
	// Move the iterator to the next element in the sorted set
	if (this->valid() == false) {
		// If the iterator is not valid, throw an exception
		throw std::exception("Invalid iterator position");
	}

	if (this->multime.elements[this->position].right != NONEXISTENT_POSITION) {
		// If the current node has a right child, move to the minimum element in the right sub-tree
		this->position = this->multime.getPositionOfMinimum(this->multime.elements[this->position].right);
	}
	else {
		// If the current node does not have a right child, go up the tree
		if (this->multime.isLeftChild(this->position) == true) {
			// If the current node is a left child, move to its parent
			this->position = this->multime.elements[this->position].parent;
		}
		else {
			// If the current node is not a left child, find the first value larger than the current one
			int auxPosition = this->multime.elements[this->position].parent;

			while (auxPosition >= 0 && this->multime.relation(this->multime.elements[auxPosition].info, this->multime.elements[this->position].info) == true) {
				if (auxPosition == 0) {
					// If it's the 'maximum' element, make the position invalid
					this->position = this->multime.arrayCapacity;
					return;
				}
				auxPosition = this->multime.elements[auxPosition].parent;
			}

			this->position = auxPosition;
		}
	}
}

TElem SortedSetIterator::getCurrent() {
	// Get the current element in the iterator
	if (this->valid() == false) {
		// If the iterator is not valid, throw an exception
		throw std::exception("Invalid iterator position");
	}

	return this->multime.elements[this->position].info;
}

bool SortedSetIterator::valid() const {
	// Check if the iterator is valid (within the range of the set and pointing to a valid element)
	return this->position >= 0 && this->position < this->multime.arrayCapacity && this->multime.elements[this->position].info != NULL_TELEM;
}
