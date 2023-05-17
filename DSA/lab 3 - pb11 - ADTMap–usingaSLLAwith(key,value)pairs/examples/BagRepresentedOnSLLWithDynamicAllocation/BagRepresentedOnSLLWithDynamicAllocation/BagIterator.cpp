#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	this->curent = c.first;
}

void BagIterator::first() {
	this->curent = this->bag.first;
}


void BagIterator::next() {
	if (!valid()){
		throw exception();
	} else {
		this->curent = curent->next();
	}
}


bool BagIterator::valid() const {
	return (this->curent!=nullptr);
}



TElem BagIterator::getCurrent() const
{
	if (!valid()){
			throw exception();
		} else {
			return this->curent->element();
		}
}
