#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->current = this->bag.first;
}

void BagIterator::first() {
	this->current = this->bag.first;
}


void BagIterator::next() {
	if (!valid()){
			throw exception();
		} else {
			this->current = this->bag.nextLink[this->current];
		}
}


bool BagIterator::valid() const {
	return (this->current!=-1);
}



TElem BagIterator::getCurrent() const
{
	if (!valid()){
		throw exception();
	} else {
		return this->bag.e[this->current];
	}
}
