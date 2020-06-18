//---------------------------------------------------------------------------
//
//  Laboratory 11                                       PriorityQueue.cpp
//
//
//
//---------------------------------------------------------------------------

#include "PriorityQueue.h"
using namespace std;


template < typename DataType, typename KeyType, typename Comparator >
PriorityQueue<DataType, KeyType, Comparator>::PriorityQueue(int maxNumber)
{
	size = 0;
	maxSize = maxNumber;
	dataItems = new DataType[maxNumber];
}


template < typename DataType, typename KeyType, typename Comparator >
void PriorityQueue<DataType, KeyType, Comparator>::enqueue(const DataType& newDataItem)

// Utilizes insert() function inherted from class Heap

{
	this->insert(newDataItem);
}


template < typename DataType, typename KeyType, typename Comparator >
DataType PriorityQueue<DataType, KeyType, Comparator>::dequeue()

// Utilizes remove() function inherted from class Heap

{
	return this->remove();
}
