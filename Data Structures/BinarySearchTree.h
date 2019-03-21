#include <list>
#include <functional>
#include <vector>
#include <set>
#pragma once

namespace data_structures {

	//TODO: Add constant static std::functions for building a list, printing, etc. to the class

	template <class K>
	class BinarySearchTree {

		K* key;

		BinarySearchTree<K>* parent;
		BinarySearchTree<K>* left;
		BinarySearchTree<K>* right;

	public:

		BinarySearchTree();
		BinarySearchTree(K&);
		BinarySearchTree(K*, size_t);
		BinarySearchTree(const std::list<K>&);
		BinarySearchTree(const std::set<K>&);
		BinarySearchTree(std::vector<K>&);
		BinarySearchTree(const BinarySearchTree<K>&);
		~BinarySearchTree();

		/*Static method for building a BST from straight left traverse.
		Takes two pointers as input: start and end + 1 (similar to qsort)
		of an array of keys.*/
		static BinarySearchTree* buildFromTraverse(K*&, K*&, K, K);

		static void sort(std::vector<K>&);

		void add(K&);
		void remove(const K&, bool = true);
		bool isEmpty() const;
		bool isLeaf() const;

		/*Methods for traversing the tree. All take as an argument
		a function which defines the action on every tree key.*/
		void straightTraverseLeft(std::function<void(K&)>&);
		void innerTraverseLeft(std::function<void(K&)>&);
		void reverseTraverseLeft(std::function<void(K&)>&);

	private:

		/*Private methods for removing tree nodes that have
		two childs. There are two ways: right and left.*/
		void rightRemove();
		void leftRemove();

	};

	/*Method implementations*/

	template<class K>
	BinarySearchTree<K>::BinarySearchTree() {
		key = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	template<class K>
	BinarySearchTree<K>::BinarySearchTree(K& key) : BinarySearchTree() {
		add(key);
	}

	template<class K>
	BinarySearchTree<K>::BinarySearchTree(K* keys, size_t n) {
		for (size_t i = 0; i < n; ++i) {
			add(keys[i]);
		}
	}

	template<class K>
	BinarySearchTree<K>::BinarySearchTree(const std::list<K>& keys) {
		for (std::list<K>::const_iterator it = keys.begin(); it != keys.end(); ++it) {
			add(*it);
		}
	}

	template<class K>
	BinarySearchTree<K>::BinarySearchTree(const std::set<K>& keys) {
		for (std::set<K>::const_iterator it = keys.begin(); it != keys.end(); ++it) {
			add(*it);
		}
	}

	template<class K>
	BinarySearchTree<K>::BinarySearchTree(std::vector<K>& keys) {
		for (std::vector<K>::iterator it = keys.begin(); it != keys.end(); ++it) {
			add(*it);
		}
	}

	template<class K>
	BinarySearchTree<K>::BinarySearchTree(const BinarySearchTree<K>& tree) {
		size_t vertices = 0;
		tree->straightTraverseLeft([&vertices](K& key) { ++vertices; });
		K* keys = new K[vertices];
		size_t count = 0;
		tree->straightTraverseLeft([&keys, &count](K& key) { keys[count++] = key; });
		buildFromTraverse(keys);
	}

	template<class K>
	BinarySearchTree<K>::~BinarySearchTree() {
		delete left;
		delete right;
		delete key;
	}

	template<>
	BinarySearchTree<int>* BinarySearchTree<int>::buildFromTraverse(int*& start, int*& end, int min, int max) {
		BinarySearchTree<int>* temp = nullptr;
		if (start < end) {
			if ((*start >= min) && (*start < max)) {
				temp = new BinarySearchTree<int>(*start);
				start++;
			}
			if (temp != nullptr) {
				temp->left = buildFromTraverse(start, end, min, *(temp->key));
				if (temp->left != nullptr) {
					temp->left->parent = temp;
				}
				temp->right = buildFromTraverse(start, end, *(temp->key), max);
				if (temp->right != nullptr) {
					temp->right->parent = temp;
				}
			}
		}
		return temp;
	}

	template<class K>
	void BinarySearchTree<K>::sort(std::vector<K>& vec) {
		BinarySearchTree<K> tree(vec);
		std::vector<K>::iterator b = vec.begin();
		std::function<void(int&)> s = [&b](int& key) { *(b++) = key; };
		tree.innerTraverseLeft(s);
	}

	template<class K>
	void BinarySearchTree<K>::add(K& key) {
		if (isEmpty()) {
			this->key = new K(key);
		}
		else {
			if (key < *(this->key)) {
				if (left != nullptr) {
					left->add(key);
				}
				else {
					left = new BinarySearchTree(key);
					left->parent = this;
				}
			}
			else if (key > *(this->key)) {
				if (right != nullptr) {
					right->add(key);
				}
				else {
					right = new BinarySearchTree(key);
					right->parent = this;
				}
			}
		}
	}

	template<class K>
	void BinarySearchTree<K>::remove(const K& key, bool useRightRemove) {
		if (key == *(this->key)) {
			BinarySearchTree<K>* newChildValue = nullptr;
			bool oneChild = true;
			if (isLeaf()) {
				newChildValue = nullptr;
			}
			else if ((left != nullptr) && (right == nullptr)) {
				newChildValue = left;
			}
			else if ((left == nullptr) && (right != nullptr)) {
				newChildValue = right;
			}
			else {
				oneChild = false;
			}
			if (oneChild) {
				if (parent != nullptr) {
					if (this == parent->left) {
						parent->left = newChildValue;
					}
					else {
						parent->right = newChildValue;
					}
					if (newChildValue != nullptr) {
						newChildValue->parent = parent;
					}
					this->parent = nullptr;
					this->left = nullptr;
					this->right = nullptr;
					delete this;
				}
				// Node to delete is the root
				else {
					BinarySearchTree<K>* temp = newChildValue;
					*(this->key) = *(newChildValue->key);
					this->left = newChildValue->left;
					this->right = newChildValue->right;
					if (left != nullptr) {
						left->parent = this;
					}
					if (right != nullptr) {
						right->parent = this;
					}
					temp->left = nullptr;
					temp->right = nullptr;
					delete temp;
				}
			}
			else {
				if (useRightRemove) {
					rightRemove();
				}
				else {
					leftRemove();
				}
			}
		}
		else if (key < *(this->key)) {
			if (left != nullptr) {
				left->remove(key);
			}
		}
		else {
			if (right != nullptr) {
				right->remove(key);
			}
		}
	}

	template<class K>
	void BinarySearchTree<K>::rightRemove() {
		BinarySearchTree<K>* finder = this->right;
		while (finder->left != nullptr) {
			finder = finder->left;
		}
		*(this->key) = *(finder->key);
		if (finder->parent != this) {
			finder->parent->left = finder->right;
			if (finder->right != nullptr) {
				finder->right->parent = finder->parent;
			}
		}
		else {
			this->right = finder->right;
			if (this->right != nullptr) {
				this->right->parent = this;
			}
		}
		finder->parent = nullptr;
		finder->left = nullptr;
		finder->right = nullptr;
		delete finder;
	}

	template<class K>
	void BinarySearchTree<K>::leftRemove() {
		BinarySearchTree<K>* finder = this->left;
		while (finder->right != nullptr) {
			finder = finder->right;
		}
		*(this->key) = *(finder->key);
		if (finder->parent != this) {
			finder->parent->right = finder->left;
			if (finder->left != nullptr) {
				finder->left->parent = finder->parent;
			}
		}
		else {
			this->left = finder->left;
			if (this->left != nullptr) {
				this->left->parent = this;
			}
		}
		finder->parent = nullptr;
		finder->left = nullptr;
		finder->right = nullptr;
		delete finder;
	}

	template<class K>
	bool BinarySearchTree<K>::isEmpty() const {
		return key == nullptr;
	}

	template<class K>
	bool BinarySearchTree<K>::isLeaf() const {
		return (left == nullptr) && (right == nullptr);
	}

	template<class K>
	void BinarySearchTree<K>::straightTraverseLeft(std::function<void(K&)>& f) {
		f(*key);
		if (left != nullptr) {
			left->straightTraverseLeft(f);
		}
		if (right != nullptr) {
			right->straightTraverseLeft(f);
		}
	}

	template<class K>
	void BinarySearchTree<K>::innerTraverseLeft(std::function<void(K&)>& f) {
		if (left != nullptr) {
			left->innerTraverseLeft(f);
		}
		f(*key);
		if (right != nullptr) {
			right->innerTraverseLeft(f);
		}
	}

	template<class K>
	void BinarySearchTree<K>::reverseTraverseLeft(std::function<void(K&)>& f) {
		if (left != nullptr) {
			left->reverseTraverseLeft(f);
		}
		if (right != nullptr) {
			right->reverseTraverseLeft(f);
		}
		f(*key);
	}

}