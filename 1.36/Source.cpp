#include <fstream>
#include <iostream>
#include "../Data Structures/BinarySearchTree.h"

int main() {
	size_t n;
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	in >> n;
	int* keys = new int[n];
	for (size_t i = 0; i < n; ++i) {
		in >> keys[i];
	}
	data_structures::BinarySearchTree<int> tree(keys, n);
	std::function<void(int&)> f = [&out](int key) { out << key << "\n"; };
	tree.straightTraverseLeft(f);
	return 0;
}