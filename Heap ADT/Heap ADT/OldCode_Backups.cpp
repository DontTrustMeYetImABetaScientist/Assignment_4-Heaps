/*

// insert and Recursive Helper
// Change to method in "Heaps" lecture slides
// Doesnt use 3 assignments and a temp variable

template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::insert(const DataType& newDataItem) throw (logic_error)
{
	try
	{
		size++;												// Update size
		dataItems[size - 1] = newDataItem;					// Add the new item to the top of the heap (i.e. the first empty array index)
		percolateUp(size - 1);								// Fix possible broken heap property
	}
	catch (logic_error e)
	{
		size--;												// Set size back equal to its correct value
															// dataItems[size] == nullptr  (Needed?)
		cout << "Insert: FULL Heap" << endl;
		e.what();
	}
}


template < typename DataType, typename KeyType, typename Comparator >
void Heap<DataType, KeyType, Comparator>::percolateUp(int currentIndex)

// Given i, root = 0, (size == 0) == empty array:
// Left: 2i
// Right: 2i + 1
// Parent: Floor(i / 2) OR (int)(i / 2)


{
	DataType* current;
	DataType* parent;
	int parentIndex;

	if (currentIndex != 0)										// Check if root
	{
		parentIndex = (int)(currentIndex / 2);					// Cast to int to ensure floor/integer division

		current = &dataItems[currentIndex];
		parent = &dataItems[parentIndex];

		if (current->getPriority() > parent->getPriority())
		{
			dataItems[parentIndex] = *current;
			dataItems[currentIndex] = *parent;

			percolateUp(parentIndex);						// Continue to check heap validity
		}
	}

	// CHECK INSTRUCTIONS when uploaded:
	// bool operator()(const KeyType &a, const KeyType &b) const { return a < b; }
	// if(current(parent))	??
}

*/