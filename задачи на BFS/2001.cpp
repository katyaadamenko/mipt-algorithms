#include <iostream>
#include <map>
#include <queue>
#include <vector>

const int orderOfNumbers = 4;

const int getMultiplier(const int orderOfNumbers) {
	int multiplier = 1;
	for (int i = 0; i < orderOfNumbers - 1; ++i)
		multiplier *= 10;
	return multiplier;
}

const int multiplier = getMultiplier(orderOfNumbers);

typedef int number_t;
typedef int previous_number_t;

int getLeftCyclicShift(int value) {
	int firstNumeral = value / multiplier;
	return (value - firstNumeral * 1000) * 10 + firstNumeral;
}

int getRightCyclicShift(int value) {
	int lastNumeral = value % 10;
	return value / 10 + lastNumeral * multiplier;
}

std::deque<number_t> findShortestPath(int firstNumber, int lastNumber) {
	std::deque<number_t> path;
	std::map<number_t, previous_number_t> visited;
	std::queue<number_t> Q;
	Q.push(firstNumber);
	visited.insert(std::make_pair(firstNumber, 0));
	number_t number;
	number_t firstNumeral, lastNumeral;
	std::vector<number_t> adjectives;
	adjectives.reserve(4);
	bool pathIsFound = false;
	while (!pathIsFound && !Q.empty()) {
		number = Q.front();
		Q.pop();
		adjectives.clear();
		firstNumeral = number / multiplier;
		lastNumeral = number % 10;
		adjectives.push_back(getLeftCyclicShift(number));
		adjectives.push_back(getRightCyclicShift(number));
		if (firstNumeral != 9) 
			adjectives.push_back(number + multiplier);
		if (lastNumeral != 1)
			adjectives.push_back(number - 1);
		for (std::vector<number_t>::iterator it = adjectives.begin(); it != adjectives.end(); ++it) {
			if (visited.find(*it) == visited.end()) {
				visited.insert(std::make_pair(*it, number));
				Q.push(*it);
			}
			if (*it == lastNumber) {
				pathIsFound = true;
				break;
			}
		}
	}
	number_t currentNumber = lastNumber;
	while (currentNumber != firstNumber) {
		path.push_front(currentNumber);
		currentNumber = visited[currentNumber];
	}
	if (firstNumber != lastNumber)
		path.push_front(firstNumber);
	return path;
}

int main() {
	int firstNumber, secondNumber;
	std::cin >> firstNumber >> secondNumber;
	std::deque<number_t> path = findShortestPath(firstNumber, secondNumber);
	while (!path.empty()) {
		std::cout << path.front() << std::endl;
		path.pop_front();
	}
	return 0;
}
