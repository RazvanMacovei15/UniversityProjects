#include "Map.h"
#include "MapIterator.h"



Map::Map()
	: capacity(10), head(-1), firstFree(0), count(0) {
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

void Map::deallocatedNode(int index) {
	nodes[index].valid = false;
	nodes[index].next = firstFree;
	firstFree = index;
}

void Map::resize() {
	Node* newNodes = new Node[2 * capacity];
	for (int i = 0; i < capacity; i++)
		newNodes[i] = nodes[i];

	for (int i = capacity; i < 2 * capacity - 1; i++) {
		newNodes[i].next = i + 1;
		newNodes[i].valid = false;
	}
	newNodes[2 * capacity - 1].next = -1;
	newNodes[2 * capacity - 1].valid = false;

	delete[] nodes;
	nodes = newNodes;
	firstFree = capacity;
	capacity *= 2;
}

Map::~Map() {
	//TODO - Implementation
	delete[] nodes;
}

TValue Map::add(TKey c, TValue v){
	//TODO - Implementation

	int current = head;
	int previous = -1;
	while (current != -1 && nodes[current].element.first != c) {
		previous = current;
		current = nodes[current].next;
	}

	if (current != -1) {
		TValue oldValue = nodes[current].element.second;
		nodes[current].element.second = v;
		return oldValue;
	}

	int newNode = allocateNode();
	nodes[newNode].element = std::make_pair(c, v);
	nodes[newNode].next = -1;
	if (previous != -1)
		nodes[previous].next = newNode;
	else
		head = newNode;

	count++;
	return NULL_TVALUE;
}

TValue Map::search(TKey c) const{
	//TODO - Implementation
	int current = head;
	while (current != -1 && nodes[current].element.first != c)
		current = nodes[current].next;

	if (current != -1)
		return nodes[current].element.second;
	return NULL_TVALUE;
}

TValue Map::remove(TKey c){
	//TODO - Implementation
	int current = head;
	int previous = -1;
	while (current != -1 && nodes[current].element.first != c) {
		previous = current;
		current = nodes[current].next;
	}

	if (current != -1) {
		TValue value = nodes[current].element.second;
		if (previous != -1)
			nodes[previous].next = nodes[current].next;
		else
			head = nodes[current].next;

		deallocatedNode(current);
		count--;
		return value;
	}

	return NULL_TVALUE;
}


int Map::size() const {
	//TODO - Implementation
	return count;
}

bool Map::isEmpty() const{
	//TODO - Implementation
	return count == 0;
}

MapIterator Map::iterator() const {
	return MapIterator(*this);
}



