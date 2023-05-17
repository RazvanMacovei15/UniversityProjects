#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator; 

/*-------------------------------------------*/

class Node;

//We define the type PNode as being the address of a Node
typedef Node *PNod;

class Node
	{
	public:
	    friend class Bag;
        //constructor
		Node(TElem e, PNod urm);
		TElem element();
		PNod next();
	private:
		TElem e;
		PNod nextNode;
};
/*-------------------------------------------*/


class Bag {

private:
	/*------------------------------------------------*/
	//first is the address of the first node in the SLL
	PNod first;
    /*------------------------------------------------*/

	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurrence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appear is the bag
	bool search(TElem e) const;

	//returns the number of occurrences for an element in the bag
	int nrOccurrences(TElem e) const;

	//returns the number of elements from the bag
	int size() const;

	//returns an iterator for this bag
	BagIterator iterator() const;

	//checks if the bag is empty
	bool isEmpty() const;

	//destructor
	~Bag();
};
