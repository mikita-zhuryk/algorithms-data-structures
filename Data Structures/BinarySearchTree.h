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

		//void buildFromTraverse(K*, size_t);

		void add(K&);
		void remove(const K&, bool = true);
		bool isEmpty() const;
		bool isLeaf() const;

		void straightTraverseLeft(std::function<void(K&)>&);
		void innerTraverseLeft(std::function<void(K&)>&);
		void reverseTraverseLeft(std::function<void(K&)>&);

	private:

		//void rightRemove(const K&);
		//void leftRemove(const K&);

	};

	template<class K>
	BinarySearchTree<K>::BinarySearchTree() {
		key = nullptr;
		parent = nullptr;
		left = nullptr;
		right = nullptr;
	}

	template<class K>
	BinarySearchTree<K>::BinarySearchTree(K& key) {
		BinarySearchTree();
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
	void BinarySearchTree<K>::remove(const K& key, bool useLeftRemove) {
		if (key == *(this->key)) {
			BinarySearchTree<K>* temp = nullptr;
			bool oneChild = true;
			if isLeaf() {
				temp = nullptr;
			}
			else if ((left != nullptr) && (right == nullptr)) {
				temp = left;
			}
			else if ((left == nullptr) && (right != nullptr)) {
				temp = right;
			}
			else {
				oneChild = false;
			}
			if (oneChild) {
				if (this == parent->left) {
					parent->left = temp;
				}
				else {
					parent->right = temp;
				}
				delete this;
			}
			else {
				if (useLeftRemove) {
					leftRemove(key);
				}
				else {
					rightRemove(key);
				}
			}
		}
		else if (key < *(this->key)) {
			left->remove(key);
		}
		else {
			right->remove(key);
		}
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