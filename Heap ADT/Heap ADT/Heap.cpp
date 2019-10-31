//-------------------------------------------------------------------------------------------
//
//  Laboratory 11 Heap ADT														Heap.cpp
//
//  Class implementation for the array implementation of the Heap ADataType
//
//-------------------------------------------------------------------------------------------
//
//	"Swapping" or "Percolate" up or down is from the perspective of the new data item
//	Thus:
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

// If the other stack is empty, we only need to clear our current stack

{
	if (dataItems != &other)							// Avoid self-assignment
	{
		if (other.isEmpty())							// No data to copy, just clear current array
		{
			clear();
		}
		else
		{
			top = other.top;
			for (int i = 0; i <= other.top; i++)
			{
				dataItems[i] = other[i];				// Deep copy data at each index of Heap other
			}
		}
	}

	return *this;										// Return a reference to the newly-populated or -cleared array
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

{
	try
	{
		//if (newDataItem.getPriority() > dataItems[size - 1].getPriority())
		if (newDataItem(dataItems[size - 1]))
			percolateUp(newDataItem, size - 1);
		else
			dataItems[size] = newDataItem;				// Add the new item to the top of the heap (i.e. the first empty array index)
		size++;											// Update size
	}
	catch (logic_error e)
	{
		size--;											// Set size back equal to its correct value
		// dataItems[size] == nullptr  (Needed?)
		cout << "Insert: FULL Heap" << endl;
		e.what();
	}
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::percolateUp(const DataType& newDataItem, int currentIndex)

// Given i (size - 1):
// Parent: Floor(i / 2) [OR] (int)(i / 2)
// In this Lab's use-case where i is unsigned, Floor and int casting are interchangable
// (Heap Lecture, slides 146 - 169)

{
	int parentIndex;

	parentIndex = (int)(currentIndex / 2);								// Cast to int to ensure floor/integer division
	dataItems[currentIndex] = dataItems[parentIndex];					// Swap down

	if (newDataItem > dataItems[currentIndex] && currentIndex != 0)			// Check for broken heap property and if root
		percolateUp(newDataItem, parentIndex);								// Continue up heap to check validity

	dataItems[parentIndex] = newDataItem;								// Once parent is bigger than newDataItem OR root, store newDataItem
}


// !! CHECK: Replace try/catch with if(empty)throw ??
template < typename DataType, typename KeyType, typename Comparator >
DataType Heap<DataType, KeyType, Comparator>::remove() throw (logic_error)

// Similar "pretending" method as insert.
// By taking the data at index size - 1 and pretending it's at index[0]
// we can compare it to its "children" at indices 1 and 2
// (Heap lecture, slides 146 - 170)
//
// By decrementing size before returning, we effectively erase the former item at index size - 1
// since the next future enqueue will overwrite whatever was stored previously (i.e. dataItems[size] = newData).

{
	DataType highestPriority;					// Create a local var to hold the data item while fixing broken heap occurs

	DataType* newRoot;							// The "new" root (See: "pretending" note in function notes above)
	DataType* leftChild;						// Root's Left Child value
	DataType* rightChild;						// Root's Right Child value


	try
	{
		highestPriority = dataItems[0];

		newRoot = dataItems[size - 1];			
		leftChild = dataItems[1];				
		rightChild = dataItems[2];				

		if (newRoot < leftChild)				// Left child greater
			percolateDown(leftChild, 1);
		else if (newRoot < rightChild)			// Right child greater
			percolateDown(rightChild, 2);
	}
	catch (logic_error e)
	{
		size++;

		cout << "Remove: EMPTY Heap" << endl;
		e.what();
	}
	
	size--;										// Update size

	return highestPriority;		// CHECK: What to return in the event of exception thrown ??
}


// TODO: Clean
template<typename DataType, typename KeyType, typename Comparator>
void Heap<DataType, KeyType, Comparator>::percolateDown(DataType& current, int currentIndex)
{
	int leftIndex = 2 * currentIndex + 1;
	int rightIndex = 2 * currentIndex + 2;

	DataType* leftChild = dataItems[leftIndex];
	DataType* rightChild = dataItems[rightIndex];
	

	if (current < leftChild)						// Left child greater
	{
		dataItems[currentIndex] = leftChild;
		percolateDown(leftChild, leftIndex);
	}
	else if (current < rightChild)					// Right child greater
	{
		dataItems[currentIndex] = rightChild;
		percolateDown(rightChild, rightIndex);
	}
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::clear()
{
	size = 0;
}


template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isEmpty() const
{
	// CHECK: Second correct?
	//return size == 0;
	return size;
}


template < typename DataType, typename KeyType, typename Comparator >
bool Heap<DataType, KeyType, Comparator>::isFull() const
{
	return size == maxSize;
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::writeLevels() const

// Given i, root = 0, (size == 0) == empty array:
// Parent: (int)(i / 2) => floor/integer division

{

	return;
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