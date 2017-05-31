#include <iostream>
#include "MergeSort.h"
#include "Qsort.h"
#include <vector>
#include <ctime>

int main() {
	int number;
	for (int j = 0; j < 5; ++j) {
		std::cin >> number;
		std::vector<int> randomArray1(number);
		for (int i = 0; i < number; ++i) {
			randomArray1[i] = i + 1;
		}
		std::random_shuffle(randomArray1.begin(), randomArray1.end());
		std::cout << "Random array:" << std::endl;
		std::vector<int> randomArray2(randomArray1);
		std::vector<int> randomArray3(randomArray1);
		std::vector<int> randomArray4(randomArray1);
		clock_t t1 = clock();
		Qsort(randomArray1.begin(), randomArray1.end(), std::less<int>(), ChooseLastElementAsPivot);
		clock_t t2 = clock();
		std::cout << "Last pivot element: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
		t1 = clock();
		Qsort(randomArray2.begin(), randomArray2.end(), std::less<int>(), ChooseRandomPivot);
		t2 = clock();
		std::cout << "Random pivot element: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
		t1 = clock();
		Qsort(randomArray3.begin(), randomArray3.end(), std::less<int>(), ChoosePivotOfThree);
		t2 = clock();
		std::cout << "Median element of three as pivot: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
		t1 = clock();
		MergeSort<std::vector<int>::iterator, int, std::less<int>>(randomArray4.begin(), randomArray4.end(), std::less<int>());
		t2 = clock();
		std::cout << "MergeSort:" << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;

		std::cin >> number;
		std::vector<int> sortedArray1(number);
		for (int i = 0; i < number; ++i)
			sortedArray1[i] = i + 1;
		std::vector<int> sortedArray2(sortedArray1);
		std::vector<int> sortedArray3(sortedArray1);
		std::vector<int> sortedArray4(sortedArray1);
		std::cout << "Sorted array:" << std::endl;
		t1 = clock();
		Qsort(sortedArray1.begin(), sortedArray1.end(), std::less<int>(), ChooseLastElementAsPivot);
		t2 = clock();
		std::cout << "Last pivot element: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
		t1 = clock();
		Qsort(sortedArray2.begin(), sortedArray2.end(), std::less<int>(), ChooseRandomPivot);
		t2 = clock();
		std::cout << "Random pivot element: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
		t1 = clock();
		Qsort(sortedArray3.begin(), sortedArray3.end(), std::less<int>(), ChoosePivotOfThree);
		t2 = clock();
		std::cout << "Median element of three as pivot: " << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
		t1 = clock();
		MergeSort<std::vector<int>::iterator, int, std::less<int>>(sortedArray4.begin(), sortedArray4.end(), std::less<int>());
		t2 = clock();
		std::cout << "MergeSort:" << (t2 - t1) / (double)CLOCKS_PER_SEC << std::endl;
	}
	char c;
	std::cin >> c;
	return 0;
}