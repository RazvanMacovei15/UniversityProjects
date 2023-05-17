#include "Map.h"
#include "MapIterator.h"
#include <exception>
using namespace std;


MapIterator::MapIterator(const Map& d) : map(d), current(d.head)
{
	//TODO - Implementation
}


void MapIterator::first() {
	//TODO - Implementation
	current = map.head;
}


void MapIterator::next() {
	//TODO - Implementation
	if (current == -1)
		throw std::exception("Invalid iterator!");

	current = map.nodes[current].next;
}


TElem MapIterator::getCurrent(){
	//TODO - Implementation

	if (current == -1)
		throw std::exception("Invalid iterator!");

	return map.nodes[current].element;
}


bool MapIterator::valid() const {
	//TODO - Implementation
	return current != -1;
}



