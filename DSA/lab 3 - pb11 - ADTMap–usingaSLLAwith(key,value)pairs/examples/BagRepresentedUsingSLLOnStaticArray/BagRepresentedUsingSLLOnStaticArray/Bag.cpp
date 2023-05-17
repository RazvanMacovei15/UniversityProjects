#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


Bag::Bag() {
	//the list is empty
	first = -1;
	//we initialize the list of free space
	for(int i=0;i<cp-1;i++){
	    nextLink[i]=i+1;
	}
	nextLink[cp-1]=-1;
	//we set the first empty position
	firstEmpty = 0;
}


int Bag::allocate() {
    //we delete the first empty slot from the list of empty slots
    int i=firstEmpty;
    firstEmpty=nextLink[firstEmpty];
    return i;
}

void Bag::deallocate(int i) {
    //we add the slot at index i at the beginning of the list of empty spaces
    nextLink[i]=firstEmpty;
    firstEmpty=i;
}

//Create one node having e as the useful information
int Bag::createNode(TElem e){
    //If you opt for a dynamic array (which is preferable), you have to resize it first, if it is empty (see Lecture 5)
    int i=allocate();
    if(i!=-1) {
        this->e[i]=e;
        nextLink[i]=-1;
    }
    return i;
}

void Bag::add(TElem elem) {
	int i=this->createNode(elem);
	if (i!=-1){
	   nextLink[i]=first;
	   first = i;
	}
}


bool Bag::remove(TElem elem) {
	bool found = false;
	int current = this->first;
	int prev = -1;
	while (current!=-1 && !found){
		if (this->e[current] == elem){
			found = true;
		} else {
			prev = current;
			current = this->nextLink[current];
		}
	}
	if (!found) {
		return false;
	} else {
		//we have to remove the element at index current
		if (prev == -1){
			this->first = this->nextLink[this->first];
		} else {
			this->nextLink[prev] = this->nextLink[current];
		}
		deallocate(current);
	    return true;
	}

}


bool Bag::search(TElem elem) const {
	bool found = false;
		int current = this->first;
		while (current!=-1 && !found){
			if (this->e[current] == elem){
				found = true;
			} else {
				current = this->nextLink[current];
			}
		}
		return found;
}

int Bag::nrOccurrences(TElem elem) const {
	int n = 0;
	int current = this->first;
	while (current!=-1){
		if (this->e[current] == elem){
			n++;
		}
		current = this->nextLink[current];
	}
	return n;
}


int Bag::size() const {
	int n = 0;
	int current = this->first;
	while (current!=-1){
		n++;
		current = this->nextLink[current];
	}
	return n;
}


bool Bag::isEmpty() const {
	return (first == -1);
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	delete[] e;
	delete[] nextLink;
}

