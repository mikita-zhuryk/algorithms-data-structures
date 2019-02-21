#include <fstream>
#include "../Data Structures/BinarySearchTree.h"
#pragma comment(linker, "/STACK:67108864")

int main() {
	std::ios_base::sync_with_stdio(false);
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