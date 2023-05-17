#pragma once
//DO NOT INCLUDE BAGITERATOR


//DO NOT CHANGE THIS PART
#define NULL_TELEM -111111;
typedef int TElem;
class BagIterator; 
class Bag {

private:
	/*------------------------------------------------------------------------------------*/
	static const int cp=180000;
	//vectorul static de elemente de tip TElem (cu spatiu fix de memorare - CAPACITATE)
    TElem e[cp];
	//vectorul static pentru egaturi
	int nextLink[cp];
	//referinta catre primul element al listei
	int first;
	//referinta catre primul element din lista spatiului liber
	int firstEmpty;
	//functii pentru alocarea/dealocarea unui spatiu liber
	//se returneaza pozitia unui spatiu liber in lista
	int allocate();
	//dealoca spatiul de indice i
	void deallocate(int i);
	//functie privata care creeaza un nod in lista inlantuita
	int createNode(TElem e);
	 /*------------------------------------------------------------------------------------*/
	//DO NOT CHANGE THIS PART
	friend class BagIterator;
public:
	//constructor
	Bag();

	//adds an element to the bag
	void add(TElem e);

	//removes one occurence of an element from a bag
	//returns true if an element was removed, false otherwise (if e was not part of the bag)
	bool remove(TElem e);

	//checks if an element appearch is the bag
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
