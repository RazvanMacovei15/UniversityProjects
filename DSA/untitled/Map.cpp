#include "Map.h"
#include "MapIterator.h"



Map::Map()
	:capacity(10), head(-1), firstFree(0), count(0){
    nodes = new Node[capacity];
    for (int i = 0; i < capacity - 1; i++) {
        nodes[i].next = i + 1;
        nodes[i].valid = false;
    }
    nodes[capacity - 1].next = -1;
    nodes[capacity - 1].valid = false;

}

int Map::allocateNode() {
    if (firstFree == -1)
        resize();

    int newNode = firstFree;
    firstFree = nodes[firstFree].next;
    nodes[newNode].valid = true;
    return newNode;
}

Map::~Map() {
	//TODO - Implementation
}

TValue Map::add(TKey c, TValue v){
	//TODO - Implementation
	return NULL_TVALUE;
}

TValue Map::search(TKey c) const{
	//TODO - Implementation
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	//TODO - Implementation
	return NULL_TVALUE;
}


int Map::size() const {
	//TODO - Implementation
	return 0;
}

bool Map::isEmpty() const{
	//TODO - Implementation
	return false;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



