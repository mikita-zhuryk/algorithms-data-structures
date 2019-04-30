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

	class DSU2D {

		vector<vector<point>> trees;

	public:

		DSU2D() : trees{ vector<vector<point>>(b, vector<point>(a, make_pair(-1, -1))) } {}

		void mergeSets(point set1Index, point set2Index) {
			if (set1Index != set2Index) {
				if (trees[set1Index.first][set1Index.second].first < trees[set2Index.first][set2Index.second].first) {
					trees[set1Index.first][set1Index.second].first += trees[set2Index.first][set2Index.second].first;
					trees[set1Index.first][set1Index.second].second = trees[set1Index.first][set1Index.second].first;
					trees[set2Index.first][set2Index.second] = set1Index;
				}
				else {
					trees[set2Index.first][set2Index.second].first += trees[set1Index.first][set1Index.second].first;
					trees[set2Index.first][set2Index.second].second = trees[set2Index.first][set2Index.second].first;
					trees[set1Index.first][set1Index.second] = set2Index;
				}
			}
		}

		point find(point what) {
			point cur = what;
			point lastCur = cur;
			while (trees[cur.first][cur.second].first > 0) {
				lastCur = cur;
				cur = trees[cur.first][cur.second];
			}
			if (cur.first > 0) {
				return cur;
			}
			return lastCur;
		}

		size_t size() const {
			return trees.size();
		}

		point& get(size_t i, size_t j) {
			return trees[i][j];
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
		rightHigh.first += b / 2;
		leftLow.second += a / 2;
		rightHigh.second += a / 2;
	}

	short area() {
		return height * width;
	}

	bool contains(point x) {
		return ((x.first >= leftLow.first) && (x.first < rightHigh.first)) && ((x.second >= leftLow.second) && (x.second < rightHigh.second));
	}

};

short getColor(vector<Rectangle>& rects, int x, int y) {
	point p = make_pair(x, y);
	for (int i = rects.size() - 1; i >= 0; --i) {
		if (rects[i].contains(p)) {
			return rects[i].color;
		}
	}
	return 1;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("in.txt");
	ofstream out("out.txt");
	short n;
	in >> a >> b >> n;
	vector<Rectangle> rects(n);
	for (size_t i = 0; i < n; ++i) {
		in >> rects[i].leftLow.first >> rects[i].leftLow.second;
		in >> rects[i].rightHigh.first >> rects[i].rightHigh.second;
		in >> rects[i].color;
		rects[i].translate();
		rects[i].calcSides();
	}
	data_structures::DSU2D rectanglesDSU;
	short color = 0;
	point cur;
	int toCheck;
	for (size_t j = 0; j < a; ++j) {
		for (size_t i = 0; i < b; ++i) {
			cur = { i, j };
			color = getColor(rects, i, j);
			//merge if colors are the same
			if ((i >= 1) && (getColor(rects, i - 1, j) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find({ i - 1, j }), rectanglesDSU.find(cur));
			}
			if ((i >= 1) && (j >= 1) && (getColor(rects, i - 1, j - 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find({ i - 1, j - 1 }), rectanglesDSU.find(cur));
			}
			if ((j >= 1) && (getColor(rects, i, j - 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find({ i, j - 1 }), rectanglesDSU.find(cur));
			}
		}
	}
	int s;
	vector<pair<short, int>> rectangleAreas;
	for (size_t i = 0; i < b; ++i) {
		for (size_t j = 0; j < a; ++j) {
			if ((s = rectanglesDSU.get(i, j).first) < 0) {
				rectangleAreas.push_back({getColor(rects, i, j), -s});
			}
		}
	}
	sort(rectangleAreas.begin(), rectangleAreas.end(), [](pair<short, int>& area1, pair<short, int>& area2) {
		return (area1.first < area2.first) || ((area1.first == area2.first) && (area1.second < area2.second));
	});
	size_t size = rectangleAreas.size();
	for (size_t i = 0; i < size; ++i) {
		out << rectangleAreas[i].first << ' ' << rectangleAreas[i].second << endl;
	}
	return 0;
}