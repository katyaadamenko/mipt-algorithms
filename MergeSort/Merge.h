#ifndef MY_MERGE
#define MY_MERGE

#include <exception>

//result != first1
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

#endif