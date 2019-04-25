#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

short a;
short b;

typedef pair<short, short> point;
typedef pair<short, int> polyArea;

namespace data_structures {

	template<typename T>
	class Tree {

		T value;
		Tree* parent;
		vector<Tree*> children;

		void add(Tree* where, T what);
		void remove(Tree* what);
		Tree* find(T what);

	};

	template<typename T>
	class DSU {

		vector<vector<pair<int, T>>> trees;
		size_t nTrees;

	public:

		void createSingleton(T& value) {
			auto vec = vector<pair<int, T>>(1);
			vec[0] = make_pair(-1, value);
			trees.push_back(vec);
			++nTrees;
		}

		void mergeSets(size_t set1Index, size_t set2Index) {
			auto tree1 = trees[set1Index];
			auto tree2 = trees[set2Index];
			if (tree1.size() > tree2.size()) {

			}
			else {

			}
			--nTrees;
		}

		size_t find(T& what) {

		}

	};

}

struct Rectangle {

	point leftLow;
	point rightHigh;
	short width;
	short height;
	short color;

	Rectangle() {
		leftLow = make_pair(-1, -1);
		rightHigh = make_pair(-1, -1);
		color = 0;
		calcSides();
	}

	Rectangle(point leftLow, point rightHigh, short color) {
		this->leftLow = leftLow;
		this->rightHigh = rightHigh;
		this->color = color;
		calcSides();
	}

	void calcSides() {
		width = rightHigh.first - leftLow.first;
		height = rightHigh.second - leftLow.second;
	}

	void translate() {
		leftLow.first += b / 2;
		rightHigh.first += b / 2 - 1;
		leftLow.second += a / 2;
		rightHigh.second += a / 2 - 1;
	}

	short area() {
		return height * width;
	}

	bool contains(point x) {
		return ((x.first >= leftLow.first) && (x.first <= rightHigh.first)) && ((x.second >= leftLow.second) && (x.second <= rightHigh.second));
	}

};

short getColor(vector<Rectangle>& rects, point p) {
	for (int i = rects.size() - 1; i >= 0; --i) {
		if (rects[i].contains(p)) {
			return rects[i].color;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("in.txt");
	ofstream out("out.txt");
	short n;
	in >> a >> b >> n;
	vector<Rectangle> rects(n + 1);
	rects[0] = Rectangle(make_pair(-b / 2, -a / 2), make_pair(b / 2, a / 2), 1);
	rects[0].translate();
	rects[0].calcSides();
	for (size_t i = 1; i < n + 1; ++i) {
		in >> rects[i].leftLow.first >> rects[i].leftLow.second;
		in >> rects[i].rightHigh.first >> rects[i].rightHigh.second;
		in >> rects[i].color;
		rects[i].translate();
		rects[i].calcSides();
	}
	bool** used = new bool*[b];
	for (size_t i = 0; i < b; ++i) {
		used[i] = new bool[a];
		for (size_t j = 0; j < a; ++j) {
			used[i][j] = false;
		}
	}
	data_structures::DSU<point> rectanglesDSU;
	short color = 0;
	point cur;
	size_t curDSUSet;
	point toCheck;
	for (size_t i = 0; i < b; ++i) {
		for (size_t j = 0; j < a; ++j) {
			used[i][j] = 1;
			cur = make_pair(i, j);
			color = getColor(rects, cur);
			curDSUSet = rectanglesDSU.find(cur);
			toCheck = make_pair(i - 1, j);
			//merge if colors are the same
			if ((i >= 1) && !used[i - 1][j] && (getColor(rects, toCheck) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find(toCheck), curDSUSet);
			}
			toCheck = make_pair(i - 1, j + 1);
			if ((i >= 1) && (j + 1 < a) && !used[i - 1][j + 1] && (getColor(rects, i - 1, j + 1) == color)) {
				rectanglesDSU.mergeSets(make_pair(i - 1, j + 1), cur);
			}
			toCheck = make_pair(i, j + 1);
			if ((j + 1 < a) && !used[i][j + 1] && (getColor(rects, i, j + 1) == color)) {
				rectanglesDSU.mergeSets(make_pair(i, j + 1), cur);
			}
			toCheck = make_pair(i, j - 1);
			if ((j >= 1) && !used[i][j - 1] && (getColor(rects, i, j - 1) == color)) {
				rectanglesDSU.mergeSets(make_pair(i, j - 1), cur);
			}
			toCheck = make_pair(i - 1, j - 1);
			if ((i >= 1) && (j >= 1) && !used[i - 1][j - 1] && (getColor(rects, i - 1, j - 1) == color)) {
				rectanglesDSU.mergeSets(make_pair(i - 1, j - 1), cur);
			}
		}
	}
	for (const auto& rect : rectanglesDSU) {
		//print, maybe sort before
	}
	system("pause");
	return 0;
}