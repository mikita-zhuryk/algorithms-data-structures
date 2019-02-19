#include <fstream>
#include "../Data Structures/BinarySearchTree.h"

int main() {
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	data_structures::BinarySearchTree<int> tree;
	size_t key;
	in >> key;
	int temp;
	while (in >> temp) {
		tree.add(temp);
	}
	tree.remove(key);
	std::function<void(int&)> print = [&out](int& key) { out << key << "\n"; };
	tree.straightTraverseLeft(print);
}