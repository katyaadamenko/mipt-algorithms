#ifndef MY_PRIORITY_QUEUE
#define MY_PRIORITY_QUEUE

#include "Heap.h"

template <typename T, typename comp>
class PriorityQueue : protected Heap<T, comp> {
public:
	PriorityQueue(int number = 0) : Heap(number) {}
	PriorityQueue(const std::vector<T> & v) : Heap(v) {}
	PriorityQueue(const T * array, int n): Heap(array, n) {}
	template <typename FwdIt>
	PriorityQueue(FwdIt first, FwdIt last): Heap(first, last) {}
	T max()const {
		return Heap<T, comp>::max();
	}
	T extract_max() {
		T oldMax = Heap<T, comp>::max();
		remove(0);
		return oldMax;
	}
	void insert(const T & newElement) {
		Heap<T, comp>::insert(newElement);
	}
};

#endif