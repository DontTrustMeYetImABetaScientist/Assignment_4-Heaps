//--------------------------------------------------------------------
//
//  Laboratory 12                                             Heap.h
//
//  Class declaration for the array implementation of the Heap ADataType
//
//--------------------------------------------------------------------

#pragma warning( disable : 4290 )

#ifndef HEAP_H
#define HEAP_H

#include <stdexcept>
#include <iostream>

using namespace std;

template < typename KeyType=int >
class Less {
  public:
    bool operator()(const KeyType &a, const KeyType &b) const { return a < b; }
};

template < typename DataType, typename KeyType=int, typename Comparator=Less<KeyType> >
class Heap
{
  public:

    static const int DEFAULT_MAX_HEAP_SIZE = 10;		// Default maximum heap size

    Heap ( int maxNumber = DEFAULT_MAX_HEAP_SIZE );		// Default constructor + basic constr
    Heap ( const Heap& other );							// Copy constructor
    Heap& operator= ( const Heap& other );				// Overloaded assignment operator

    ~Heap ();											// Destructor

    void insert ( const DataType &newDataItem )			// Insert a data item
        throw ( logic_error );
	DataType remove() throw (logic_error);				// Remove max priority element
    void clear ();										// Clear heap

    bool isEmpty () const;								// Heap is empty
    bool isFull () const;								// Heap is full

    void showStructure () const;						// Output the heap structure

	void percolateUp(const DataType&, int);				// Insert helper
	//void percolateDown();								// Remove helper
	//void leveler(int, int);							// writeLevels helper

  private:

    void showSubtree ( int index, int level ) const;	// Recursive helper for showStructure

    int maxSize,			// Maximum number of elements in the heap
        size;				// Actual number of elements in the heap
    DataType *dataItems;	// Array containing the heap elements

    Comparator comparator;
};

#endif	//#ifndef HEAP_H
