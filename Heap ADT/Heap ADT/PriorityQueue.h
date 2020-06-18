//--------------------------------------------------------------------
//
//  Laboratory 12, Programming Exercise 1              PriorityQueue.h
//
//  Class declaration for the heap implementation of the
//  Priority Queue ADT -- inherits the array implementation of the
//  Heap ADT
//
//--------------------------------------------------------------------

#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdexcept>
#include <iostream>

using namespace std;

#include "Heap.cpp"
#include "Heap.h"

const int defMaxQueueSize = 10;   // Default maximum queue size

template < typename DataType, typename KeyType=int, typename Comparator=Less<KeyType> >
class PriorityQueue : public Heap<DataType>
{
  public:

    // Constructor
    PriorityQueue ( int maxNumber = defMaxQueueSize );

    // Queue manipulation operations
    void enqueue ( const DataType &newDataItem );   // Enqueue data element
    DataType dequeue ();                            // Dequeue data element

private:

	int maxSize,			// Maximum number of elements in the PQ
		size;				// Actual number of elements in the PQ
	DataType *dataItems;	// Array containing the PQ elements
};

#endif
