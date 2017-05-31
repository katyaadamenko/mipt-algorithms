#include <iostream>
#include "Heap.h"
#include "PriorityQueue.h"
#include <functional>

int main() {
	size_t n;
	std::cin >> n;
	std::vector<int> v1;
	v1.reserve(n);
	for (size_t i = 0; i < n; ++i)
		v1.push_back(i);
	Heap<int, std::less<int>> heap(v1.begin(), v1.end());
	for (size_t i = 0; i < heap.size(); ++i)
		std::cout << heap[i] << ' ';
	std::cout << std::endl;
	size_t index;
	std::cin >> index;
	heap.remove(index);
	for (size_t i = 0; i < heap.size(); ++i)
		std::cout << heap[i] << ' ';
	std::cout << std::endl;
	
	Heap<int, std::less<int>> heap2(v1);
	for (size_t i = 0; i < heap2.size(); ++i)
		std::cout << heap2[i] << ' ';
	std::cout << std::endl;

	int * array = new int[n];
	for (size_t i = 0; i < n; ++i)
		array[i] = i;

	Heap < int, std::less<int>> heap3(array, n);
	for (size_t i = 0; i < heap3.size(); ++i)
		std::cout << heap3[i] << ' ';
	std::cout << std::endl;
	heap3.insert(9);
	for (size_t i = 0; i < heap3.size(); ++i)
		std::cout << heap3[i] << ' ';
	std::cout << std::endl;

	Heap <int, std::less<int>> heap4;
	int value;
	std::cin >> n;
	for (size_t i = 0; i < n; ++i) {
		std::cin >> value;
		heap4.insert(value);
	}
	for (size_t i = 0; i < heap4.size(); ++i)
		std::cout << heap4[i] << ' ';
	std::cout << std::endl;

	delete[] array;
	char c;
	std::cin >> c;
}