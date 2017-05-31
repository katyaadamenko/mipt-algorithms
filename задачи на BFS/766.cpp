#include <iostream>
#include <vector>
#include <algorithm>

template <class FwdIt, class Compare>
FwdIt Merge(FwdIt first1, FwdIt last1, FwdIt first2, FwdIt last2, FwdIt result, Compare cmp) {
	while (first1 != last1 && first2 != last2) {
		if (cmp(*first1, *first2)) {
			*result++ = *first1;
			++first1;
		}
		else {
			*result++ = *first2;
			++first2;
		}
	}
	while (first1 != last1) {
		*result++ = *first1;
		++first1;
	}
	while (first2 != last2) {
		*result++ = *first2;
		++first2;
	}
	return result;
}

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

int main() {
	int n;
	std::cin >> n;
	std::vector<int> v(n);
	for (int i = 0; i < n; ++i)
		std::cin >> v[i];
	//std::vector<int> additionalMemory(n);
	MergeSort<std::vector<int>::iterator, int, std::less<int>>(v.begin(), v.end(), std::less<int>());
	for (int i = 0; i < n; ++i)
		std::cout << v[i] << ' ';
	return 0;
}