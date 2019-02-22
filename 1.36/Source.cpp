#include <fstream>
#include <list>
#include <vector>
#include "../Data Structures/BinarySearchTree.h"
#pragma comment(linker, "/STACK:67108864")

void printList(std::list<int> list, std::ostream& out) {
	size_t count = 0;
	size_t size = list.size();
	for (std::list<int>::iterator it = list.begin(); it != list.end(); ++it) {
		out << *it;
		if (count < size - 1) {
			out << " ";
		}
		++count;
	}
}

int main() {
	std::ios_base::sync_with_stdio(false);
	size_t n;
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> n;
	std::vector<int> keys(n);
	for (size_t i = 0; i < n; ++i) {
		in >> keys[i];
	}
	data_structures::BinarySearchTree<int> tree;
	std::list<int> result;
	std::function<void(int&)> buildList = [&result](int key) { result.push_back(key); };
	tree = *data_structures::BinarySearchTree<int>::buildFromTraverse(keys);
	tree.reverseTraverseLeft(buildList);
	printList(result, out);
	result.clear();
	out << "\n";
	tree.innerTraverseLeft(buildList);
	printList(result, out);
	return 0;
}