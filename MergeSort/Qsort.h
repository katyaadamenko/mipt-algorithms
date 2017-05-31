#ifndef QSORT_H
#define QSORT_H

#include <iostream>
#include <cstdlib>
#include <algorithm>

template <class RndIt, class Predicate>
RndIt ChooseLastElementAsPivot(RndIt first, RndIt last, Predicate comp) {
	return last - 1;
}

template <class RndIt, class Predicate>
RndIt ChooseRandomPivot(RndIt first, RndIt last, Predicate comp) {
	RndIt pivot = rand() % (last - first) + first;
	std::swap(*(last - 1), *pivot);
	return last - 1;
}

template <class RndIt, class Predicate>
RndIt FindMedianOfThree(RndIt first, RndIt second, RndIt third, Predicate comp) {
	RndIt result;
	if (comp(*first, *second)) {
		if (comp(*second, *third))
			result = second;
		else if (comp(*first, *third))
			result = third;
		else
			result = first;
	}
	else if (comp(*first, *third))
		result = first;
	else if (comp(*second, *third))
		result = third;
	else
		result = second;
	return result;
}

template <class RndIt, class Predicate>
RndIt ChoosePivotOfThree(RndIt first, RndIt last, Predicate comp) {
	RndIt median = (last - first) / 2 + first;
	RndIt pivot = FindMedianOfThree(first, median, last - 1, comp);
	std::swap(*(last - 1), *pivot);
	return last - 1;
}

template <class RndIt, class Predicate>
void Qsort(RndIt first, RndIt last, Predicate comp, RndIt(*ChoosePivot) (RndIt, RndIt, Predicate)) {
	if (last - first > 1) {
		RndIt it = Partition(first, last, comp, ChoosePivot);
		Qsort(first, it, comp, ChoosePivot);
		Qsort(it + 1, last, comp, ChoosePivot);
	}
}

template <class RndIt, class Predicate>
RndIt Partition(RndIt first, RndIt last, Predicate comp, RndIt(*ChoosePivot) (RndIt, RndIt, Predicate)) {
	RndIt pivot = ChoosePivot(first, last, comp);
	RndIt i;
	bool iInArray = false;
	for (RndIt j = first; j != last - 1; ++j) {
		if (comp(*j, *pivot)) {
			if (iInArray)
				++i;
			else {
				i = first;
				iInArray = true;
			}
			std::swap(*i, *j);
		}
	}
	if (iInArray)
		++i;
	else {
		i = first;
		iInArray = true;
	}
	std::swap(*i, *(last - 1));
	return i;
}

#endif