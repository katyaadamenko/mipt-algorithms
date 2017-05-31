#ifndef MY_HEAPSORT
#define MY_HEAPSORT

#include <iostream>
#include <vector>
#include <exception>

template <typename T, typename Comp>
class Heap {
private:
	std::vector <T> _heap;
	size_t left(int i)const {
		/*if (i < 0)
			throw std::out_of_range("Wrong i");*/
		return 2 * i + 1;
	}
	size_t right(int i)const {
		/*if (i < 0)
			throw std::out_of_range("Wrong i");*/
		return 2 * i + 2;
	}
	size_t parent(int i)const {
		/*if (i < 0)
			throw std::out_of_range("Wrong i");*/
		return i / 2 - 1 + i % 2;
	}
	void build_heap() {
		for (int i = _heap.size() / 2; i >= 0; --i)
			sift_down(i);
	}
public:
	Heap(int number = 0) {
		_heap.reserve(number);
	}
	Heap(const std::vector<T> & v) :_heap(v) {
		build_heap();
	}
	Heap(const T * array, int n) {
		_heap.reserve(n);
		for (int i = 0; i < n; ++i)
			_heap.push_back(array[i]);
		build_heap();
	}
	template <typename FwdIt>
	Heap(FwdIt first, FwdIt last) {
		for (FwdIt it = first; it != last; ++it)
			_heap.push_back(*it);
		build_heap();
	}
	int size()const {
		return _heap.size();
	}
	void insert(const T & newElement) {
		_heap.push_back(newElement);
		sift_up(_heap.size() - 1);
	}
	void sift_down(int i);
	void sift_up(int i);
	void remove(int i);
	T & operator [] (int i) {
		return _heap.at(i);
	}
};

template <typename T, typename Comp>
void Heap<T, Comp>::sift_down(int i) {
	int largest;
	if (left(i) < _heap.size() && Comp()(_heap[i], _heap[left(i)]))
		largest = left(i);
	else
		largest = i;
	if (right(i) < _heap.size() && Comp()(_heap[largest], _heap[right(i)]))
		largest = right(i);
	if (i != largest) {
		std::swap(_heap[i], _heap[largest]);
		sift_down(largest);
	}
}

template <typename T, typename Comp>
void Heap<T, Comp>::sift_up(int i) {
	T value = _heap[i];
	while (i > 0 && Comp()(_heap[parent(i)], value)) {
		_heap[i] = _heap[parent(i)];
		i = parent(i);
	}
	_heap[i] = value;
}

template <typename T, typename Comp>
void Heap<T, Comp>::remove(int i) {
	std::swap(_heap.at(i), _heap[_heap.size() - 1]);
	_heap.pop_back();
	sift_down(i);
}

template <typename T, typename RndIt, typename Comp>
void Heapsort(RndIt first, RndIt last, Comp comp) {
	Heap<T, Comp> heap(first, last);
	int size = heap.size();
	for (int i = 0; i < size - 1; ++i) {
		std::swap(heap[heap.size() - 1], heap[0]);
		*(last - 1 - i) = heap[heap.size() - 1];
		heap.remove(heap.size() - 1);
		heap.sift_down(0);
	}
	*first = heap[0];
}

/*template <typename T, typename Comp>
void Heapsort(std::vector<T> & v, Comp comp) {
	Heap<T, Comp> heap(v);
	int size = heap.size();
	for (int i = 0; i < size - 1; ++i) {
		std::swap(heap[heap.size() - 1], heap[0]);
		v[v.size() - 1 - i] = heap[heap.size() - 1];
		heap.remove(heap.size() - 1);
		heap.sift_down(0);
	}
	v[0] = heap[0];
}*/

int main() {
	int number;
	std::cin >> number;
	std::vector<int> v;
	v.reserve(number);
	int value;
	for (int i = 0; i < number; ++i) {
		std::cin >> value;
		v.push_back(value);
	}
	Heapsort<int, std::vector<int>::iterator, std::less<int> >(v.begin(), v.end(), std::less<int>());
	//Heapsort(v, std::less<int>());
	for (std::vector<int>::iterator it = v.begin(); it != v.end(); ++it)
		std::cout << *it << ' ';
	return 0;
}



#endif