#include <list>
#include <functional>
#include <vector>
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
		static BinarySearchTree* buildFromTraverse(std::vector<K>&);

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
	BinarySearchTree<K>* BinarySearchTree<K>::buildFromTraverse(std::vector<K>& vec) {
		size_t size = vec.size();
		std::vector<K> diff(size - 1);
		for (size_t i = 0; i < size - 1; ++i) {
			diff[i] = vec[i + 1] - vec[i];
		}
		BinarySearchTree<K>* result = new BinarySearchTree<K>(vec[0]);
		BinarySearchTree<K>* cur;
		int summ_diff = diff[0];
		bool startedRight = false;
		if (diff[0] < 0) {
			result->left = new BinarySearchTree<K>(vec[1]);
			result->left->parent = result;
			cur = result->left;
		}
		else {
			result->right = new BinarySearchTree<K>(vec[1]);
			result->right->parent = result;
			cur = result->right;
		}
		for (size_t i = 1; i < size - 1; ++i) {
			summ_diff += diff[i];
			if (!startedRight && (summ_diff >= 0)) {
				result->right = new BinarySearchTree<K>(vec[i + 1]);
				result->right->parent = result;
				cur = result->right;
				startedRight = true;
			}
			else {
				if ((diff[i] > 0) && (diff[i - 1] < 0)) {
					//go up
					if (cur->parent != result) {
						BinarySearchTree<K>* up = cur->parent;
						while (vec[i + 1] > *(up->parent->key)) {
							up = up->parent;
						}
						up->right = new BinarySearchTree<K>(vec[i + 1]);
						up->right->parent = up;
					}
					else {
						cur->right = new BinarySearchTree<K>(vec[i + 1]);
						cur->right->parent = cur;
					}
				}
				else if ((diff[i] < 0) && (diff[i - 1] > 0)) {
					//go up
					if (cur->parent != result) {
						BinarySearchTree<K>* up = cur->parent;
						while (vec[i + 1] < *(up->parent->key)) {
							up = up->parent;
						}
						up->left = new BinarySearchTree<K>(vec[i + 1]);
						up->left->parent = up;
					}
					else {
						cur->left = new BinarySearchTree<K>(vec[i + 1]);
						cur->left->parent = cur;
					}
				}
				else if ((diff[i] < 0) && (diff[i - 1] < 0)) {
					cur->left = new BinarySearchTree<K>(vec[i + 1]);
					cur->left->parent = cur;
					cur = cur->left;
				}
				else if ((diff[i] > 0) && (diff[i - 1] > 0)) {
					cur->right = new BinarySearchTree<K>(vec[i + 1]);
					cur->right->parent = cur;
					cur = cur->right;
				}
			}
		}
		return result;
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