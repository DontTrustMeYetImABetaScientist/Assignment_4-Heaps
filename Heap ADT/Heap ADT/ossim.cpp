//--------------------------------------------------------------------
//
//  Laboratory 11, Programming Exercise 1                  ossim.cpp
//
//  Operating system task scheduling simulation
//
//--------------------------------------------------------------------

// Simulates an operating system's use of a priority queue to regulate
// access to a system resource (printer, disk, etc.).

#include "config.h"

#if LAB11_PQ

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "PriorityQueue.cpp"

using namespace std;

//--------------------------------------------------------------------
//
// Declaration for the task data struct
//

struct TaskData
{
    int getPriority () const
        { return priority; }     // Returns the priority. Needed by the heap.

    int priority,                // Task's priority
        arrived;                 // Time when task was enqueued

};


//--------------------------------------------------------------------

int main ()
{
    PriorityQueue<TaskData, int, Less<int> > taskPQ;   // Priority queue of tasks
    TaskData task;               // Task
    int simLength,               // Length of simulation (minutes)
        minute,                  // Current minute
        numPtyLevels,            // Number of priority levels
        numArrivals,             // Number of new tasks arriving
        j;                       // Loop counter

    // Seed the random number generator
    srand((unsigned int)time(NULL));

    cout << endl << "Enter the number of priority levels : ";
    cin >> numPtyLevels;

    cout << "Enter the length of time to run the simulator : ";
    cin >> simLength;

    for ( minute = 0 ; minute < simLength ; minute++ )
    {
        // [INSTRUCTIONS]: Dequeue the first task in the queue (if any).

		if (!taskPQ.isEmpty())
		{
			task = taskPQ.remove();					// Dequeue a task

			// [INSTRUCTIONS]: Output current task's priority, when it was enqueued, and how long it waited in queue
			
			int waitTime = minute - task.arrived;	// Total time task waited in queue

			cout << "TASK REMOVED: "
				 << "Priority Level (" << task.getPriority() << ") "
				 << "Time Added to Queue (" << task.arrived << ") "  
				 << "Time Waited In Queue: " << waitTime << endl;
		}
		else
		{
			cout << "Queue Is EMPTY" << endl;		// No tasks to dequeue
		}

        // [INSTRUCTIONS]: Determine the number of new tasks and add them to the queue.

		// Possible Scenarios:
		// Given numArrivals is "k"		
		// (a) k = 0, 3		Do not add any tasks to the queue
		// (b) k = 1		Add 1 task
		// (c) k = 2		Add 2 tasks
		
		numArrivals = rand() % 4;					// Determine # of tasks to enqueue

		if (numArrivals == 1 || numArrivals == 2)
		{
			int currentArrivalTime = minute;				// Record the "time" when tasks will be enqueued

			for (j = 0; j < numArrivals; j++)		 
			{
				task.priority = rand() % numPtyLevels;		// Give each task a rand priority level
				task.arrived = currentArrivalTime;			// Document the time of enqueue
				taskPQ.insert(task);						// Enqueue the new task
			}
		}

    }// end simulation for-loop

    return 0;
}

#endif