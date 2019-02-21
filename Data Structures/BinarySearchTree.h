#include <list>
#include <functional>
#include <set>
#pragma once

namespace data_structures {

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
		BinarySearchTree(const BinarySearchTree<K>&);
		~BinarySearchTree();

		/*Static method for building a BST from straight left traverse.
		Takes two pointers as input: start and end + 1 (similar to qsort)
		of an array of keys.*/
		static BinarySearchTree* buildFromTraverse(K*, K*);

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

	template<class K>
	BinarySearchTree<K>* BinarySearchTree<K>::buildFromTraverse(K* start, K* end) {
		if (start < end) {
			BinarySearchTree<K>* temp = new BinarySearchTree<K>(*start);
			K* leftSub = start;
			while ((leftSub < end) && (*(++leftSub) < *start));
			temp->left = buildFromTraverse(start + 1, leftSub);
			if (temp->left != nullptr) {
				temp->left->parent = temp;
			}
			temp->right = buildFromTraverse(leftSub, end);
			if (temp->right != nullptr) {
				temp->right->parent = temp;
			}
			return temp;
		}
		else {
			return nullptr;
		}
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
				if (this == parent->left) {
					parent->left = newChildValue;
				}
				else {
					parent->right = newChildValue;
				}
				this->left = nullptr;
				this->right = nullptr;
				delete this;
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
		else if ((key < *(this->key)) && (left != nullptr)) {
			left->remove(key);
		}
		else if (right != nullptr) {
			right->remove(key);
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
			finder->parent->left = nullptr;
		}
		else {
			this->right = finder->right;
			if (this->right != nullptr) {
				this->right->parent = this;
			}
			finder->right = nullptr;
		}
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
			finder->parent->right = nullptr;
		}
		else {
			this->left = finder->left;
			if (this->left != nullptr) {
				this->left->parent = this;
			}
			finder->left = nullptr;
		}
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