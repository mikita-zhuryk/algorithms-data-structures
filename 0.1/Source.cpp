#include <fstream>
#include <list>

struct TreeNode {

	int* key;
	TreeNode* left;
	TreeNode* right;

	TreeNode() {
		key = nullptr;
		left = nullptr;
		right = nullptr;
	}

	TreeNode(int& key) {
		this->key = new int(key);
		left = nullptr;
		right = nullptr;
	}

	void add(int& key) {
		if (this->key == nullptr) {
			this->key = new int(key);
		}
		else {
			if (key < *(this->key)) {
				if (left != nullptr) {
					left->add(key);
				}
				else {
					left = new TreeNode(key);
				}
			}
			else if (key > *(this->key)) {
				if (right != nullptr) {
					right->add(key);
				}
				else {
					right = new TreeNode(key);
				}
			}
		}
	}

	void straightTraverseLeft(std::ofstream& out) {
		out << *key << std::endl;
		if (left != nullptr) {
			left->straightTraverseLeft(out);
		}
		if (right != nullptr) {
			right->straightTraverseLeft(out);
		}
	}

};

int main() {
	int temp;
	std::ifstream in("input.txt");
	std::ofstream out("output.txt");
	TreeNode tree;
	while (in >> temp) {
		tree.add(temp);
	}
	tree.straightTraverseLeft(out);
	return 0;
}