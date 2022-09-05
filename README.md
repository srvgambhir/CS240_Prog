# CS240_Prog

This program implements a priority queue in 3 ways

Implementation 1: A singly linked list that is ordered by priority where the largest priority is in the front of the list. If the two items have the same priority, then the tie is broken by ordering the item with the smallest value first

Implementation 2: A max-heap implemented with a dynamic array. When the first item is inserted, an array of length 1 is dynamically allocated to accommodate the first item. Then the doubling strategy is used to reallocate the dynamic array when more space is required. Similarly, if after removing an item, only 25% or
less of the dynamic array contains items, the size of the dynamic array is reallocated to be twice the number of items in the dynamic array.

Implementation 3: A vector of queues. Each index i of the vector points to a queue of items where each item in the queue has priority i; if no items of priority i exist, this pointer is left as NULL. At all times, the
vector is appropriately sized to be 1 + largest priority stored in the priority queue. The insert/delete (enqueue/dequeue, pushback/popfront) queue functions run in O(1) time.

The main function accepts the following commands:

- i num priority : inserts an item (priority, timestamp) into priority queue num.
- d num : removes the item with the highest priority from priority queue num and prints the priority and timestamp to stdout - the two integers are separated by a space anda newline follows the second integer. If the priority queue is empty, does nothing.
- l num : prints (but does not remove) the item with the highest priority from priority queue num. Prints the priority and timestamp to stdout - the two integers are separated by a space and a newline follows the second integer. If the priority queue is empty, does nothing.
- r : initializes or resets all priority queues to be empty.
- x : terminates the program

At the top of the program is the runtime and space analysis for each implementation.
