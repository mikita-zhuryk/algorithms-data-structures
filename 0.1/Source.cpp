#include <fstream>
#include "../Data Structures/BinarySearchTree.h"

int main() {
	int temp;
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	data_structures::BinarySearchTree<int> tree;
	while (in >> temp) {
		tree.add(temp);
	}
	std::function<void(int&)> print = [&out](int& key) { out << key << "\n"; };
	tree.straightTraverseLeft(print);
	return 0;
}