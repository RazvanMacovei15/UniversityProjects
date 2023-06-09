#include "SortedSet.h"
#include "SortedSetIterator.h"
#include <iostream>

SortedSet::SortedSet(Relation r) {
	this->arrayCapacity = INITIAL_CAPACITY;
	this->elements = new Node[this->arrayCapacity];     // Create a dynamic array to hold the nodes of the BST
	this->nextEmpty = new int[this->arrayCapacity];     // Create an array to track the next empty positions in the elements array

	for (int i = 0; i < this->arrayCapacity; i++) {
		this->elements[i] = NULL_NODE;                   // Initialize each element in the elements array to a NULL_NODE value
		this->nextEmpty[i] = i + 1;                       // Set the nextEmpty array to link each position to the next empty position
	}

	this->elementCount = 0;                              // Initialize the count of elements to 0
	this->relation = r;                                  // Set the relation (comparison function) for the SortedSet
	this->rootPosition = NONEXISTENT_POSITION;           // Set the root position of the BST to a non-existent position

	// The root will be placed at position 0, so the first empty position is 1
	this->firstEmpty = 1;
	this->nextEmpty[this->arrayCapacity - 1] = NONEXISTENT_POSITION;   // Set the last position in the nextEmpty array to indicate non-existence
}


int SortedSet::findPositionOf(TComp elem) const {
	int position = this->rootPosition;

	if (this->rootPosition == NONEXISTENT_POSITION) { // If the set is empty
		return NONEXISTENT_POSITION; // Return non-existent position
	}

	while (position < this->arrayCapacity and this->elements[position].info != NULL_TELEM) {
		if (this->elements[position].info == elem) { // If the current position contains the desired element
			return position; // Return the position
		}

		// If it has a left child and the element is smaller according to the relation
		if (this->relation(elem, this->elements[position].info) == true and this->elements[position].left != NONEXISTENT_POSITION) {
			position = this->elements[position].left; // Move to the left child position
		}

		// If it has a right child and the element is greater or equal according to the relation
		else if (this->relation(elem, this->elements[position].info) == false and this->elements[position].right != NONEXISTENT_POSITION) {
			position = this->elements[position].right; // Move to the right child position
		}

		else {
			return NONEXISTENT_POSITION; // Return non-existent position if the element is not found in the BST
		}
	}

	return NONEXISTENT_POSITION; // Return non-existent position if the element is not found in the BST
}

void SortedSet::addNewNode(TComp elem, int position, bool isLeftChild, int parentPosition) {
	this->elements[position].info = elem;
	this->elements[position].left = NONEXISTENT_POSITION;
	this->elements[position].right = NONEXISTENT_POSITION;
	this->elements[position].parent = parentPosition;
	this->elementCount++;

	if (parentPosition == NONEXISTENT_POSITION) { // If it is a root
		this->rootPosition = position; // Set the root position to the current position
	}
	else { // Update the left/right child of the parent
		if (isLeftChild == true) { // If it is a left child
			this->elements[parentPosition].left = position; // Set the left child of the parent to the current position
		}
		else { // If it is a right child
			this->elements[parentPosition].right = position; // Set the right child of the parent to the current position
		}
	}
}


void SortedSet::resizeArrays() {
	// Create new arrays with double the capacity
	Node* auxArray = new Node[2 * this->arrayCapacity + 1];
	int* auxEmpty = new int[2 * this->arrayCapacity + 1];

	// Copy elements from the old arrays to the new arrays
	for (int i = 0; i < this->arrayCapacity; i++) {
		auxArray[i] = this->elements[i];
	}

	// Initialize the remaining elements in the new arrays with NULL_NODE
	for (int i = this->arrayCapacity; i < 2 * this->arrayCapacity + 1; i++) {
		auxArray[i] = NULL_NODE;
	}

	// Delete the old arrays and assign the new arrays
	delete[] this->elements;
	this->elements = auxArray;

	// Update the nextEmpty array with the new capacity
	for (int i = 0; i < 2 * this->arrayCapacity + 1; i++) {
		auxEmpty[i] = i + 1;
	}
	auxEmpty[2 * this->arrayCapacity] = NONEXISTENT_POSITION;

	// Delete the old nextEmpty array and assign the new array
	delete[] this->nextEmpty;
	this->nextEmpty = auxEmpty;

	// Update the arrayCapacity to the new capacity
	this->arrayCapacity = 2 * this->arrayCapacity + 1;
}


bool SortedSet::isLeftChild(int position) const {
	// Check if the given position is a valid node and it is not the root position
	// Then, compare the left child of the parent node with the given position
	return (position != NONEXISTENT_POSITION && position != this->rootPosition && this->elements[this->elements[position].parent].left == position);
}

bool SortedSet::isRightChild(int position) const {
	// Check if the given position is a valid node and it is not the root position
	// Then, compare the right child of the parent node with the given position
	return (position != NONEXISTENT_POSITION && position != this->rootPosition && this->elements[this->elements[position].parent].right == position);
}

int SortedSet::getPositionOfMaximum(int rootPosition) const {
	// Start from the given rootPosition and traverse to the rightmost node (maximum value)
	while (rootPosition < this->arrayCapacity && this->elements[rootPosition].right != NONEXISTENT_POSITION) {
		rootPosition = this->elements[rootPosition].right;
	}

	return rootPosition;
}


int SortedSet::getPositionOfMinimum(int rootPosition) const {
	// Start from the given rootPosition and traverse to the leftmost node (minimum value)
	while (rootPosition < this->arrayCapacity && this->elements[rootPosition].left != NONEXISTENT_POSITION) {
		rootPosition = this->elements[rootPosition].left;
	}

	return rootPosition;
}

void SortedSet::addToNextEmpty(int position) {
	// Set the next empty position of the given position to the current firstEmpty position
	this->nextEmpty[position] = this->firstEmpty;
	// Update the firstEmpty position to the given position
	this->firstEmpty = position;
}


void SortedSet::removeWithNoSuccessors(int position) {
	// Add the given position to the nextEmpty list
	this->addToNextEmpty(position);

	if (this->isLeftChild(position) == true) {
		// Update the left child of the parent to NONEXISTENT_POSITION since the node is being removed
		this->elements[this->elements[position].parent].left = NONEXISTENT_POSITION;
	}
	else if (this->isRightChild(position) == true) {
		// Update the right child of the parent to NONEXISTENT_POSITION since the node is being removed
		this->elements[this->elements[position].parent].right = NONEXISTENT_POSITION;
	}
	else {
		// If the node being removed is the root, update the rootPosition to NONEXISTENT_POSITION
		this->rootPosition = NONEXISTENT_POSITION;
	}

	// Set the removed node to NULL_NODE
	this->elements[position] = NULL_NODE;
}


void SortedSet::removeWithOneSuccessor(int position, bool hasLeftChild) {
	// Add the given position to the nextEmpty list
	this->addToNextEmpty(position);

	if (this->isLeftChild(position) == true) {
		if (hasLeftChild == true) {
			// Update the left child of the parent to the left child of the node being removed
			this->elements[this->elements[position].parent].left = this->elements[position].left;
			// Update the parent of the left child
			this->elements[this->elements[position].left].parent = this->elements[position].parent;
		}
		else { // has a right child
			// Update the left child of the parent to the right child of the node being removed
			this->elements[this->elements[position].parent].left = this->elements[position].right;
			// Update the parent of the right child
			this->elements[this->elements[position].right].parent = this->elements[position].parent;
		}
	}
	else if (this->isRightChild(position) == true) {
		if (hasLeftChild == true) {
			// Update the right child of the parent to the left child of the node being removed
			this->elements[this->elements[position].parent].right = this->elements[position].left;
			// Update the parent of the left child
			this->elements[this->elements[position].left].parent = this->elements[position].parent;
		}
		else { // has a right child
			// Update the right child of the parent to the right child of the node being removed
			this->elements[this->elements[position].parent].right = this->elements[position].right;
			// Update the parent of the right child
			this->elements[this->elements[position].right].parent = this->elements[position].parent;
		}
	}
	else { // root
		// The node being removed is the root, and it has one child, which will become the new root
		int rootCopy = this->rootPosition;
		if (hasLeftChild == true) {
			// Update the rootPosition to the left child
			this->rootPosition = this->elements[rootCopy].left;
			// Update the parent of the new root to NONEXISTENT_POSITION since it becomes the new root
			this->elements[this->elements[rootCopy].left].parent = NONEXISTENT_POSITION;
		}
		else {
			// Update the rootPosition to the right child
			this->rootPosition = this->elements[rootCopy].right;
			// Update the parent of the new root to NONEXISTENT_POSITION since it becomes the new root
			this->elements[this->elements[rootCopy].right].parent = NONEXISTENT_POSITION;
		}
	}

	// Set the removed node to NULL_NODE
	this->elements[position] = NULL_NODE;
}


void SortedSet::removeWithTwoSuccessors(int position) {
	// Find the position of the maximum element in the left subtree
	int positionOfMaximum = this->getPositionOfMaximum(this->elements[position].left);
	// Replace the node to be removed with the maximum element in the left subtree
	this->elements[position] = this->elements[positionOfMaximum];

	// Add the position of the maximum element to the nextEmpty list
	this->addToNextEmpty(positionOfMaximum);

	if (this->isLeftChild(positionOfMaximum) == true) {
		// Update the left child of the parent to NONEXISTENT_POSITION
		this->elements[this->elements[positionOfMaximum].parent].left = NONEXISTENT_POSITION;
	}
	else if (this->isRightChild(positionOfMaximum) == true) {
		// Update the right child of the parent to NONEXISTENT_POSITION
		this->elements[this->elements[positionOfMaximum].parent].right = NONEXISTENT_POSITION;
	}

	// Set the removed node to NULL_NODE
	this->elements[positionOfMaximum] = NULL_NODE;
}


void SortedSet::resetEmpty() {
	// Reset the nextEmpty array to point to the next position in sequence
	for (int i = 0; i < this->arrayCapacity; i++) {
		this->nextEmpty[i] = i + 1;
	}
	// Set the last position in the array to NONEXISTENT_POSITION to mark the end of the list
	this->nextEmpty[this->arrayCapacity - 1] = NONEXISTENT_POSITION;
	// Set the firstEmpty to the first available position (1, assuming position 0 is used for the root)
	this->firstEmpty = 1;
}


void SortedSet::independentListsCopy(const SortedSet& originalSet) {
	// Check if the originalSet is the same as the current set, in which case no copy is needed
	if (this == &originalSet) {
		return;
	}

	// Check if the array capacity is different, in which case reallocation is required
	if (this->arrayCapacity != originalSet.arrayCapacity) {
		// Delete the existing arrays
		delete[] this->elements;
		delete[] this->nextEmpty;

		// Allocate new arrays with the capacity of the original set
		this->elements = new Node[originalSet.arrayCapacity];
		this->nextEmpty = new int[originalSet.arrayCapacity];
	}

	// Copy the elements and nextEmpty arrays from the original set
	for (int i = 0; i < originalSet.arrayCapacity; i++) {
		this->elements[i] = originalSet.elements[i];
		this->nextEmpty[i] = originalSet.nextEmpty[i];
	}
}

bool SortedSet::add(TComp elem) {
	int position = this->rootPosition;
	int parentPosition = NONEXISTENT_POSITION;
	bool isLeftChild = false; // if this is false => right child

	if (this->rootPosition == NONEXISTENT_POSITION) { // the set is empty
		this->resetEmpty();
		this->addNewNode(elem, 0, isLeftChild, NONEXISTENT_POSITION);
		return true;
	}

	while (position < this->arrayCapacity) {
		if (this->elements[position].info == NULL_TELEM) {
			// Found an empty position, add the new node here
			this->addNewNode(elem, position, isLeftChild, parentPosition);
			return true;
		}
		parentPosition = position;

		if (this->elements[position].info == elem) {
			return false; // Element already exists in the set, cannot add it again
		}

		if (this->relation(elem, this->elements[position].info) == true) { // left child
			position = this->elements[position].left;
			isLeftChild = true;
		}
		else { // right child
			position = this->elements[position].right;
			isLeftChild = false;
		}

		if (position == NONEXISTENT_POSITION) {
			if (this->firstEmpty == NONEXISTENT_POSITION) { // array is full, need to resize
				position = this->arrayCapacity;
				this->resizeArrays();
				this->firstEmpty = position + 1; // the next empty position is the one after the previous capacity
			}
			else {
				// Get the next empty position from the list of empty positions
				position = this->firstEmpty;
				this->firstEmpty = this->nextEmpty[this->firstEmpty];
			}
		}
	}

	return true;
}


bool SortedSet::remove(TComp elem) {
	int position = this->findPositionOf(elem);
	int successorCount = 0;
	bool hasLeftChild = false;

	if (position == NONEXISTENT_POSITION) {
		return false; // Element doesn't exist in the set, cannot remove it
	}

	// Check the number of successors (children) of the node at the given position
	if (this->elements[position].left != NONEXISTENT_POSITION) {
		successorCount++;
		hasLeftChild = true;
	}
	if (this->elements[position].right != NONEXISTENT_POSITION) {
		successorCount++;
	}

	if (successorCount == 0) {
		// Node has no successors, directly remove it
		this->removeWithNoSuccessors(position);
	}
	else if (successorCount == 1) {
		// Node has one successor, remove it by updating the parent's link
		this->removeWithOneSuccessor(position, hasLeftChild);
	}
	else {
		// Node has two successors, replace it with the maximum node from the left subtree
		this->removeWithTwoSuccessors(position);
	}

	this->elementCount--;
	return true;
}


bool SortedSet::search(TComp elem) const {
	// Check if the element exists in the set by finding its position
	return this->findPositionOf(elem) != NONEXISTENT_POSITION;
}

int SortedSet::size() const {
	// Return the number of elements in the set
	return this->elementCount;
}

bool SortedSet::isEmpty() const {
	// Check if the set is empty by comparing the element count to zero
	return this->elementCount == 0;
}

int SortedSet::getRange() const {
	if (this->rootPosition == NONEXISTENT_POSITION) {
		// The set is empty, so there is no range
		return -1;
	}

	// Find the positions of the maximum and minimum elements in the set
	int positionOfMaximum = this->getPositionOfMaximum(this->rootPosition);
	int positionOfMinimum = this->getPositionOfMinimum(this->rootPosition);

	// Calculate and return the range as the difference between the maximum and minimum elements
	return this->elements[positionOfMaximum].info - this->elements[positionOfMinimum].info;
}


SortedSetIterator SortedSet::iterator() const {
	// Create and return a SortedSetIterator initialized with a reference to the current set
	return SortedSetIterator(*this);
}

SortedSet::SortedSet(const SortedSet& originalSet) {
	// Copy the member variables from the original set
	this->elementCount = originalSet.elementCount;
	this->arrayCapacity = originalSet.arrayCapacity;
	this->firstEmpty = originalSet.firstEmpty;
	this->rootPosition = originalSet.rootPosition;
	this->relation = originalSet.relation;

	// Copy the elements and nextEmpty arrays using independentListsCopy function
	this->independentListsCopy(originalSet);
}

SortedSet& SortedSet::operator=(const SortedSet& originalSet) {
	if (this != &originalSet) {
		// Copy the member variables from the original set
		this->elementCount = originalSet.elementCount;
		this->arrayCapacity = originalSet.arrayCapacity;
		this->firstEmpty = originalSet.firstEmpty;
		this->rootPosition = originalSet.rootPosition;
		this->relation = originalSet.relation;

		// Copy the elements and nextEmpty arrays using independentListsCopy function
		this->independentListsCopy(originalSet);
	}

	return *this;
}

SortedSet::~SortedSet() {
	// Delete the dynamically allocated arrays
	delete[] this->elements;
	delete[] this->nextEmpty;
}
