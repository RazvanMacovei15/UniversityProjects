#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;

Node::Node(TElem e, PNod next) {
	this->e = e;
	this->nextNode = next;
}

TElem Node::element() {
	return e;
}

PNod Node::next() {
	return this->nextNode;
}

Bag::Bag() {
	first = nullptr;
}


void Bag::add(TElem elem) {
	PNod q = new Node(elem, nullptr);
	q->nextNode = first;
	first = q;
}


bool Bag::remove(TElem elem) {
	bool found = false;
	PNod p = this->first;
	PNod previous = nullptr;
	while (p!=nullptr && !found){
		if (p->element()==elem){
			found=true;
			//We have to delete the first node of the list
			if (previous==nullptr){
				this->first = this->first->next();
				delete p;
			//We have delete the node after the one pointed by previous
			} else {
				previous->nextNode = p->next();
				delete p;
			}
		} else {
			previous = p;
			p = p->next();
		}
	}
	return found;
}


bool Bag::search(TElem elem) const {
	PNod p = this->first;
	while (p!=nullptr){
		if (p->element()==elem){
			return true;
		} else {
			p = p->next();
		}
	}
	return false;
}

int Bag::nrOccurrences(TElem elem) const {
	int nrO = 0;
	PNod p = this->first;
	while (p!=nullptr){
		if (p->element()==elem){
			nrO++;
		}
		p = p->next();
	}
	return nrO;
}


int Bag::size() const {
	int nr = 0;
	PNod p = this->first;
	while (p!=nullptr){
		nr++;
		p = p->next();
	}
	return nr;
}


bool Bag::isEmpty() const {
	return (this->first == nullptr);
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	//We free the memory allocated for the nodes of the SLL
	while (first != nullptr) {
		PNod p = first;
		first = first->nextNode;
		delete p;
	}
}

