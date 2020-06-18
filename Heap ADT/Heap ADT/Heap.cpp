//-------------------------------------------------------------------------------------------
//
//  Laboratory 11 Heap ADT														Heap.cpp
//
//  Class implementation for the array implementation of the Heap ADataType
//
//-------------------------------------------------------------------------------------------
//
//	"Swapping" or "Percolate" up or down is from the perspective of the new data item
//	Thus:3
//		1. Swapping UP -> Enqueue when new item is GREATER than its parent
//		2. Swapping DOWN -> Dequeue when new item is LESS than a child
//
//	Variable int size indicates directly how many items are in the array.
//	To access the largest unfilled index use dataItems[size]
//
//-------------------------------------------------------------------------------------------

#include "Heap.h"

using namespace std;


template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(int maxNumber)

// Size of 0 indicates an empty Heap

{
	size = 0;
	maxSize = maxNumber;
	dataItems = new DataType[maxNumber];
}


template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::Heap(const Heap& other)
{
	dataItems = other;
	return *this;
}


template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>& Heap<DataType, KeyType, Comparator>::operator=(const Heap& other)
{
	if (dataItems != &other)							// Avoid self-assignment
	{
		if (!other.isEmpty())							// No data to copy, just clear current array
		{
			size = other.size;
			for (int i = 0; i < other.size; i++)
			{
				dataItems[i] = other[i];				// Deep copy data at each index of Heap other
			}
		}
		else
			clear();									// Heap other is empty, clear current Heap
	}

	return *this;								// Return a reference to the newly-populated or -cleared array
}


template < typename DataType, typename KeyType, typename Comparator >
Heap<DataType, KeyType, Comparator>::~Heap()
{
	delete[] dataItems;
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::insert(const DataType& newDataItem) throw (logic_error)

// By doing the value check before assigning the new value and calling percolateUp 
// we reduce the swap assignments to 2 (vs 3 using a temp var) 
// by "pretending" that the newDataItem is at index size and compare it to index size - 1

// Comparator true when a is less than b

// Given i = size
// Parent Index: Floor((i - 1) / 2) [OR] (int)((i - 1) / 2)

{
	// Intermediate variables to make if-conditional easier to read:
	int parentIndex = (int)((size - 1) / 2);
	bool parentIsLess = newDataItem.getPriority() > dataItems[parentIndex].getPriority();
	

	try
	{
		if (size == 0)
			dataItems[0] = newDataItem;					// Heap is empty, add newDataItem as root
		else if (parentIsLess)
			percolateUp(newDataItem, size);				// Heap property broken, call resursive helper
		else
			dataItems[size] = newDataItem;				// Add the new item to the top of the heap (i.e. the first empty array index)

		size++;											// Update size
	}
	catch (logic_error e)
	{
		size--;											// Set size back equal to its correct value
		e.what();

		cout << "Insert: FULL Heap" << endl;
	}
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::percolateUp(const DataType& newDataItem, int currentIndex)

// Given i, size 0 indicates empty heap:
// Parent Index: Floor((i - 1) / 2) [OR] (int)((i - 1) / 2)

// Comparator true when a is less than b

// In this Lab's use-case where i is unsigned, Floor and int casting are interchangable
// (Heap Lecture, Slides 146 - 169)

{
	// Intermediate variables to make conditionals easier to read
	int parentIndex = (int)((currentIndex - 1) / 2);						
	bool parentIsLess = newDataItem.getPriority() > dataItems[parentIndex].getPriority();
	
	do
	{
		dataItems[currentIndex] = dataItems[parentIndex];				// Store parent's data in the current index
		dataItems[parentIndex] = newDataItem;							// Swap UP new data to parent's array position

		currentIndex = parentIndex;										// Update the current index
		parentIndex = (int)((currentIndex - 1) / 2);					// Update the new parent index

		parentIsLess = newDataItem.getPriority() > dataItems[parentIndex].getPriority();		// Check if parent is still less
	} while (parentIsLess && currentIndex != 0);
}



template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)

// By decrementing size before returning, we effectively erase the former item at index [size - 1],
// since the next future enqueue will overwrite whatever was stored previously (i.e. dataItems[size] = newData).

// Use of a while loop allows for checking of both parent v child values as well as if children exist (incld which is larger)

{
	DataType highestPriority;
	DataType newData;

	int currentIndex;											// Placeholder for indices being worked on
	bool heapPropertyBroken;									// Indicator if children are larger than the new root

	if (this->isEmpty())
		throw logic_error("Remove: EMPTY Heap");				// No items to remove
	
	highestPriority = dataItems[0];
	newData = dataItems[size - 1];

	heapPropertyBroken = true;
	currentIndex = 0;														// Start at the root (i.e. index 0)

	// Fix possible broken heap property (up to the largest array index if needed)
	while (heapPropertyBroken && currentIndex < size)						
	{
		// Right child largest => focus on index [(i * 2) + 2] instead of [(i * 2) + 1]
		if (dataItems[currentIndex].getPriority() < dataItems[currentIndex + 1].getPriority() && currentIndex < (size - 1))
			currentIndex++;

		// The new root's data is the largest, heap validity restored
		if (newData.getPriority() >= dataItems[currentIndex].getPriority())										
		{
			heapPropertyBroken = false;
		}
		else
		{
			dataItems[(currentIndex - 1) / 2] = dataItems[currentIndex];		// Heap still invalid, continue fix
			currentIndex = 2 * currentIndex + 1;
		}
	}

	dataItems[(currentIndex - 1) / 2] = newData;								// Final index in focus is correct position for the new root data
	size--;																		// Update size to reflect removal of 1 item

	return highestPriority;														// Return the highest priority item stored at start of fxn
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::clear()
{
	size = 0;
}


template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	return size == 0;
}


template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
	return size == maxSize;
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::showStructure() const

// Outputs the priorities of the data items in a heap in both array
// and tree form. If the heap is empty, outputs "Empty heap". This
// operation is intended for testing/debugging purposes only.

{
	int j;   // Loop counter

	cout << endl;
	if (size == 0)
		cout << "Empty heap" << endl;
	else
	{
		cout << "size = " << size << endl;       // Output array form
		for (j = 0; j < maxSize; j++)
			cout << j << "\t";
		cout << endl;
		for (j = 0; j < size; j++)
			cout << dataItems[j].getPriority() << "\t";
		cout << endl << endl;
		showSubtree(0, 0);                        // Output tree form
	}
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::showSubtree(int index, int level) const

// Helper function for the showStructure() function. Outputs the
// subtree (subheap) whose root is stored in dataItems[index]. Argument
// level is the level of this dataItems within the tree.

{
	int j;   // Loop counter

	if (index < size)
	{
		showSubtree(2 * index + 2, level + 1);        // Output right subtree
		for (j = 0; j < level; j++)        // Tab over to level
			cout << "\t";
		cout << " " << dataItems[index].getPriority();   // Output dataItems's priority
		if (2 * index + 2 < size)                // Output "connector"
			cout << "<";
		else if (2 * index + 1 < size)
			cout << "\\";
		cout << endl;
		showSubtree(2 * index + 1, level + 1);        // Output left subtree
	}
}

