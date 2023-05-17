#include "SortedBag.h"
#include "SortedBagIterator.h"
#include <cmath>




SortedBag::SortedBag(Relation r) {
    this->rel = r;
    this->capacity = 10;
    this->sz = 0;
    this->elements = new TComp[this->capacity];
    this->counters = new int[this->capacity];
    for (int i = 0; i < this->capacity; i++) {
        this->counters[i] = 0;
    }
}

void SortedBag::resize() {
    int newCapacity = this->capacity * 2;
    TComp* newElements = new TComp[newCapacity];
    int* newCounters = new int[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newCounters[i] = 0;
    }
    for (int i = 0; i < this->sz; i++) {
        int index = hash(this->elements[i]) % newCapacity;
        while (newCounters[index] != 0) {
            index = (index + 1) % newCapacity;
        }
        newElements[index] = this->elements[i];
        newCounters[index] = this->counters[i];
    }
    delete[] this->elements;
    delete[] this->counters;
    this->elements = newElements;
    this->counters = newCounters;
    this->capacity = newCapacity;
}

void SortedBag::add(TComp e) {
    if (this->sz == this->capacity) {
        resize();
    }
    int index = hash(e) ;
    int initialIndex = index;

    // Find the correct position to insert the element while maintaining the sorted order
    while (this->counters[index] != 0 && this->rel(this->elements[index], e)) {
        index = (index + 1) ;
        // Stop if we have traversed the entire array
        if (index == initialIndex) {
            // Resize and recalculate the index
            resize();
            index = hash(e) ;
        }
    }

    // Shift elements to make space for the new element
    for (int i = this->sz; i > index; i--) {
        this->elements[i] = this->elements[i - 1];
        this->counters[i] = this->counters[i - 1];
    }

    // Insert the new element at the correct position
    this->elements[index] = e;
    this->counters[index]++;

    this->sz++;
}


bool SortedBag::remove(TComp e) {
    int index = hash(e) /*% this->capacity*/;
    while (this->counters[index] != 0) {
        if (this->elements[index] == e) {
            this->counters[index]--;
            if (this->counters[index] == 0) {
                // Shift elements to fill the empty slot
                int nextIndex = (index + 1) /*% this->capacity*/;
                while (this->counters[nextIndex] != 0) {
                    int newIndex = hash(this->elements[nextIndex]) /*% this->capacity*/;
                    if ((nextIndex > index && (newIndex <= index || newIndex > nextIndex)) ||
                        (nextIndex < index && (newIndex <= index && newIndex > nextIndex))) {
                        this->elements[index] = this->elements[nextIndex];
                        this->counters[index] = this->counters[nextIndex];
                        index = nextIndex;
                    }
                    nextIndex = (nextIndex + 1) /*% this->capacity*/;
                }
                this->counters[index] = 0;
            }
            this->sz--;
            return true;
        }
        index = (index + 1) ;
    }
    return false;
}

bool SortedBag::search(TComp elem) const {
    int index = hash(elem) /*% this->capacity*/;
    while (this->counters[index] != 0) {
        if (this->elements[index] == elem) {
            return true;
        }
        index = (index + 1) ;
    }
    return false;
}

int SortedBag::nrOccurrences(TComp elem) const {
    int index = hash(elem) ;
    int initialIndex = index;

    // Find the element in the hash table
    while (this->counters[index] != 0) {
        if (this->elements[index] == elem) {
            return this->counters[index];
        }
        index = (index + 1) ;
        // Stop if we have traversed the entire array
        if (index == initialIndex) {
            break;
        }
    }

    return 0;
}


int SortedBag::size() const {
    return this->sz;
}

bool SortedBag::isEmpty() const {
    return this->sz == 0;
}

SortedBagIterator SortedBag::iterator() const {
    return SortedBagIterator(*this);
}

SortedBag::~SortedBag() {
    delete[] this->elements;
    delete[] this->counters;
}

int SortedBag::hash(TComp e) const {
    // Ensure e is a non-negative value
    if (e < 0) {
        e = -e;
    }

    // Perform division hashing
    return e % this->capacity;
}