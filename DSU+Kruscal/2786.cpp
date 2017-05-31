#include <iostream>
#include <vector>
#include <exception>
#include <string>

typedef int vertex_t;
typedef int weight_t;

class DSU {
	std::vector<int> parentsOfElements;
	std::vector<weight_t> weightsOfTrees;
public:
	DSU(int numberOfElements = 0) {
		/*if (numberOfElements < 0)
			throw std::out_of_range("Impossible to make DSU: wrong number of elements");*/
		for (int i = 0; i < numberOfElements; ++i)
			make_set();
	}
	void make_set() {
		weightsOfTrees.push_back(1);
		parentsOfElements.push_back(parentsOfElements.size());
	}
	int find_set(int element) {
		/*if (element < 0)
			throw std::out_of_range("Impossible to find set. Wrong number of element");*/
		if (parentsOfElements[element] != element)
			return parentsOfElements[element] = find_set(parentsOfElements[element]);
		return element;
	}
	void union_sets(int first, int second);
};

void DSU::union_sets(int first, int second) {
	first = find_set(first);
	second = find_set(second);
	if (first != second) {
		if (weightsOfTrees[first] < weightsOfTrees[second])
			std::swap(first, second);
		parentsOfElements[second] = first;
		if (weightsOfTrees[first] == weightsOfTrees[second])
			++weightsOfTrees[first];
	}
}

struct Command {
	char firstLetter;
	vertex_t first;
	vertex_t second;
	Command(char firstLetter, vertex_t first, vertex_t second) : firstLetter(firstLetter), first(first), second(second) {}
};


int main() {
	int n, m, k;
	std::cin >> n >> m >> k;
	DSU dsu(n);
	std::vector<Command> commands;
	commands.reserve(k);
	std::string command;
	vertex_t first, second;
	for (int i = 0; i < m; ++i)
		std::cin >> first >> second;
	for (int i = 0; i < k; ++i) {
		std::cin >> command >> first >> second;
		command == "ask" ? commands.push_back(Command('a', first - 1, second - 1)) : commands.push_back(Command('c', first - 1, second - 1));
	}
	std::vector<bool> answers;
	answers.reserve(k - m);
	for (std::vector<Command>::reverse_iterator it = commands.rbegin(); it != commands.rend(); ++it) {
		if (it->firstLetter == 'c')
			dsu.union_sets(it->first, it->second);
		else {
			answers.push_back(dsu.find_set(it->first) == dsu.find_set(it->second));
		}
	}
	for (std::vector<bool>::reverse_iterator it = answers.rbegin(); it != answers.rend(); ++it) {
		*it ? (std::cout << "YES") : (std::cout << "NO");
		std::cout << std::endl;
	}
	return 0;
}