#ifndef MY_HEAP
#define MY_HEAP

#include <vector>
#include <exception>

template <typename T, typename comp>
class Heap {
private:
	std::vector <T> _heap;
	size_t left(size_t i)const {
		if (i < 0)
			throw std::out_of_range("Wrong i");
		return 2 * i + 1;
	}
	size_t right(size_t i)const {
		if (i < 0)
			throw std::out_of_range("Wrong i");
		return 2 * i + 2;
	}
	size_t parent(size_t i)const {
		if (i < 0)
			throw std::out_of_range("Wrong i");
		return (i - 1) / 2;
	}
	void build_heap() {
		for (int i = _heap.size() / 2; i >= 0; --i)
			sift_down(i);
	}
protected:
	const T max()const {
		return _heap.at(0);
	}
public:
	Heap(size_t number = 0) {
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
	size_t size()const {
		return _heap.size();
	}
	void insert(const T & newElement) {
		_heap.push_back(newElement);
		sift_up(_heap.size() - 1);
	}
	void sift_down(size_t i);
	void sift_up(size_t i);
	void remove(size_t i);
	T & operator [] (size_t i) {
		return _heap.at(i);
	}
};

template <typename T, typename comp>
void Heap<T, comp>::sift_down(size_t i) {
	int largest;
	if (i < 0 || i >= _heap.size())
		throw std::out_of_range("Wrong i. Impossible to sift down");
	if (left(i) < _heap.size() && comp()(_heap[i], _heap[left(i)]))
		largest = left(i);
	else
		largest = i;
	if (right(i) < _heap.size() && comp()(_heap[largest], _heap[right(i)]))
		largest = right(i);
	if (i != largest) {
		std::swap(_heap[i], _heap[largest]);
		sift_down(largest);
	}
}

template <typename T, typename comp>
void Heap<T, comp>::sift_up(size_t i) {
	if (i < 0 || i >= _heap.size())
		throw std::out_of_range("Wrong i. Impossible to sift up");
	T value = _heap[i];
	while (i > 0 && comp()(_heap[parent(i)], value)) {
		_heap[i] = _heap[parent(i)];
		i = parent(i);
	}
	_heap[i] = value;
}

template <typename T, typename comp>
void Heap<T, comp>::remove(size_t i) {
	std::swap(_heap.at(i), _heap[_heap.size() - 1]);
	_heap.pop_back();
	sift_down(i);
}

#endif