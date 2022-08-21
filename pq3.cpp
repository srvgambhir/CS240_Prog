/*
 * Linked List:
 * 	- The run time of the Linked List implementation is approximately O(n^2) in the worst case
 * 		- We are storing items in the linked list according to their priorities, as such deleteMax is trivial (we return the head of the list)
 * 		- However, this means that insertion is more costly, as we must determine the correct position to place a new element based on the sorting order
 * 			- must traverse the linked list for each insertion (this is Theta(n) in the worst case)
 *		- Therefore, in the worst case, deleteMax and lookMax have constant run time, and insertion has linear runtime.
 *			- Since we will be performing insertion "n" times, the worst case runtime is thus O(n^2)
 *			- Note that insertion has best case run time O(1), the new element fits into the sorted order where we begin searching for it
 *			- As such, the best case run time for the linked list implementation is O(n)
 *	- The auxilliary space required for this implementation is O(1)
 *		- Aside from the space required for the elements in the list, we are not allocating other memory on the heap
 *
 * Max Heap implemented with a Dynamic Array:
 * 	- The run time of this implementation is O(nlogn)
 * 		- Insert takes O(logn) time -> essentially placing a new item at the first free leaf and "bubbling" it up until it reaches its correct place
 * 		- In the worst case, this new item would traverse the full height of the heap (which is logn)
 * 		- Similarly, in the case of deleteMax, we are swapping the root node (the max) with the last leaf.
 * 		- This might result in the heap-order property being violated, and so we move the root down the heap into its appropriate place
 * 		- In the worst case, this element would traverse the full height of the heap (which is logn)
 * 		- Since any priority queue can be used to sort in time O(initialization + n*insert + n*deleteMax), this means that this implementation has runtime O(nlogn)
 * 		- Note that the implementation of dynamic arrays (i.e. expand by doubling as needed) only takes O(1) extra time -> amortized over all insertions
 * 	- The auxiliary space required for this implementation is O(1)
 * 		- We are not allocating new memory throughout the execution of the program (except for implementing the doubling strategy for dynamic arrays, in which case the allocated memory is replaced rather than added onto)
 * 		- Thus the auxillary space required is O(1)
 *
 * Vector of Queues:
 * 	- Let k represent the largest priority stored in the priority queue
 * 	- The runtime of this implementation would then be O(k)
 * 		- The primary vector storing the queues is sized depending on the largest priority entered
 * 		- This vector is constantly resized to be 1 + largest priority, and so the runtime (since the insert and delete functions for queue run in O(1) time) is O(k)
 
   */


#include <iostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>
#include <queue>
#include <math.h>
using namespace std;

// Linked List

class Node{

	public:

	pair<int, int> p;
	Node *next = NULL;
	 
	Node(pair<int, int> p1) : p{p1} {}

        ~Node() {
                if (next != NULL) {
                        delete next;
                }
        }
};

void insert(Node **pq, pair<int, int> p1) {
	Node *tmp = new Node(p1);

	if (p1.first > (*pq)->p.first) {
		tmp->next = *pq;
		*pq = tmp;
	}
	else {
		Node *current = *pq;
		while (current->next != NULL && p1.first <= (current->next->p).first) {
			current = current->next;
		}
	tmp->next = current->next;
	current->next = tmp;	
		}
}

void deleteMax(Node **pq) {
	Node *tmp = *pq;
	*pq = tmp->next;
	tmp->next = NULL;
	cout << (tmp->p).first << " " << (tmp->p).second <<  endl;
	delete tmp;
}

void peek(Node **pq) {
	cout << ((*pq)->p).first << " " << ((*pq)->p).second << endl;
}


// Dynamic Array

class DynArray {

	public:
		int size = 0;
		int cap = 0;
		pair<int, int> *arr = NULL;

		~DynArray () {
			if (arr != NULL) {
				delete [] arr;
			}
		}

		int parent(int i) {
			return floor((i-1) / 2);
		}

		int left(int i) {
			return 2*i + 1;
		}

		int right(int i) {
			return 2*i + 2;
		}

		void reset() {
			if (arr != NULL) {
				delete [] arr;
			}
			arr = NULL;
			this->size = 0;
			this->cap = 0;
		}

		void insert(pair<int, int> p) {

			if (this->size == 0) {
				arr = new pair<int, int>[1];
				++cap;
			}
			else if (this->size == this->cap) {
				this->cap *= 2;
				int n_size = this->cap;
				pair<int, int> *tmp = new pair<int, int>[n_size];
				for (int i = 0; i < this->size; ++i) {
					tmp[i] = arr[i];
				}
				delete [] arr;
				arr = tmp;
			}

			arr[this->size] = p;

			int i = this->size;
			for (int pt = parent(i); pt >= 0 && arr[pt].first < arr[i].first; pt = parent(i)) {
				pair<int, int> tmp = arr[pt];

				arr[pt] = arr[i];
				arr[i] = tmp;
				i = pt;
			}
			this->size += 1;
		}

		void deleteMax() {
			this->size -= 1;
			cout << arr[0].first << " " << arr[0].second << endl;
			arr[0] = arr[this->size];

			int i = 0;

			for (int lt = left(i); lt < this->size; lt = left(i)) {
				int rt = right(i);
				int j = lt;

				if (rt < this->size && arr[rt].first > arr[j].first) {
					j = rt;
				}
				if (arr[i].first > arr[j].first) break;
				pair<int, int> tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i = j;
			}

			if (this->size <= 0.25*this->cap) {
				int n_size = this->size*2;
				this->cap = n_size;
				pair<int, int> *tmp = new pair<int, int>[n_size];
				for (int i = 0; i < this->size; ++i) {
					tmp[i] = arr[i];
				}
				delete [] arr;
				arr = tmp;
			}
		}

		void peek() {
			cout << arr[0].first << " " <<  arr[0].second << endl;
		}
};


int main() {
	int stamp{0};
	string input;
	string cmd;
	int num{0};
	int pr{0};

	Node *pq = NULL;

	DynArray *heap = new DynArray;

	vector<queue<int> *> v;
	
	while (getline(cin, input)) {
		istringstream stream(input);
		stream >> cmd;

		if (cmd == "r") {

			// Linked List
			delete pq;
			pq = NULL;
			
			// Dynamic Array
			heap->reset();

			// Vector of Queues
			while (!v.empty()) {
				delete v.back();
				v.pop_back();
			}
			

                }
		else if(cmd == "i") {
			stamp += 1;

			stream >> num;
			stream >> pr;

			pair<int, int> p1(pr, stamp);
			
			if (num == 1) {
				if (pq == NULL) {
					pq = new Node(p1);
				}
				else {
					insert(&pq, p1);
				}
			}

			if (num == 2) {
				heap->insert(p1);
			}

			if (num == 3) {
				int len = v.size();

				if (len <= p1.first) {
					v.resize(p1.first + 1, nullptr);
				}
				queue<int> *new_q = v[p1.first];
				if (new_q == nullptr) {
					new_q = new queue<int>;

				}	
				new_q->push(p1.second);
				v[p1.first] = new_q;
			}

		}
		else if (cmd == "d") {
			stream >> num;
			
			if(num == 1) {
				if (pq != NULL) {
					deleteMax(&pq);
				}
			}

			if(num == 2) {
				if (heap->size != 0) {
					heap->deleteMax();
				}
			}
			if (num == 3) {
				int len = v.size();
				if (len - 1 <= 0) {
					continue;
				}
				else {
					cout << len - 1 << " " << v[len - 1]->front() << endl;
					v[len - 1]->pop();

					if (v[len - 1]->empty()) {
						delete v.back();
						v.pop_back();

						while (!v.empty()) {
							if(v.back()) {
								break;
							}
							delete v.back();
							v.pop_back();
						}
					}

				}

			}
		}
		else if (cmd == "l") {
			stream >> num;
			if(num == 1) {
				if (pq != NULL) {
					peek(&pq);
				}
			}

			if(num == 2) {
				if (heap->size != 0) {
					heap->peek();
				}
			}
			
			if (num == 3) {
				int len = v.size();
				if (len - 1 <=  0) {
					continue;
				}
				else {
					if (!v[len - 1]->empty()) {
						cout << len - 1 << " " << v[len-1]->front() << endl;
					}
				}
			}
		}
		else if (cmd == "x") {

			// Linked List
			delete pq;

			// Dynamic Array
			delete heap;

			// Vector of Queues
			while (!v.empty()) {
				delete v.back();
				v.pop_back();
			}

			break;
		}
	}
}
