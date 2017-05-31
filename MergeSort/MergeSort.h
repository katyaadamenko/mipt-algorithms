#ifndef MY_MERGESORT
#define MY_MERGESORT

#include "Merge.h"
#include <vector>
#include <algorithm>

template <class RndIt, class T, class Compare>
void MergeSort(RndIt begin, RndIt end, Compare cmp) {
	std::vector<T> additionalMemory(end - begin);
	if (begin + 1 != end) {
		RndIt median = begin + (end - begin) / 2;
		MergeSort<RndIt, T, Compare>(begin, median, cmp);
		MergeSort<RndIt, T, Compare>(median, end, cmp);
		Merge(begin, median, median, end, additionalMemory.begin(), cmp);
		copy(additionalMemory.begin(), additionalMemory.end(), begin);
	}
}

#endif
