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
			//since DSU is built upon a 2D array, we must work with both indices. If a vertex is a root,
			//its value is equal to (-n, -n), where n is the number of elements in the tree
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
			while (cur.first >= 0) {
				lastCur = cur;
				cur = trees[cur.first][cur.second];
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

	class DSU {

		vector<int> trees;

	public:

		DSU(size_t n) : trees(n * n, -1) {}

		void mergeSets(int root1, int root2) {
			if (root1 != root2) {
				if (trees[root1] <= trees[root2]) {
					trees[root1] += trees[root2];
					trees[root2] = root1;
				}
				else {
					trees[root2] += trees[root1];
					trees[root1] = root2;
				}
			}
		}

		int find(int what) {
			int cur = what;
			int lastCur = cur;
			while (cur >= 0) {
				lastCur = cur;
				cur = trees[cur];
			}
			return lastCur;
		}

		size_t size() const {
			return trees.size();
		}

		int get(size_t i) {
			return trees[i];
		}

	};

}

struct Rectangle {

	point leftLow;
	point rightHigh;
	short color;

	Rectangle() {
		leftLow = make_pair(-1, -1);
		rightHigh = make_pair(-1, -1);
		color = 0;
	}

	Rectangle(point leftLow, point rightHigh, short color) {
		this->leftLow = leftLow;
		this->rightHigh = rightHigh;
		this->color = color;
	}

	void translate() {
		leftLow.first += b / 2;
		rightHigh.first += b / 2;
		leftLow.second += a / 2;
		rightHigh.second += a / 2;
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

void drawColors(vector<Rectangle>& rects) {
	short** colors = new short*[b];
	for (short i = 0; i < b; ++i) {
		colors[i] = new short[a];
		for (short j = 0; j < a; ++j) {
			colors[i][j] = getColor(rects, i, j);
		}
	}
	for (short j = a - 1; j >= 0; --j) {
		for (short i = 0; i < b; ++i) {
			cout << (short)colors[i][j] << ' ';
		}
		cout << endl;
	}
	for (short i = 0; i < b; ++i) {
		delete[] colors[i];
	}
	delete[] colors;
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
	}
	int m = max(a, b);
	data_structures::DSU rectanglesDSU(m);
	short color = 0;
	int cur;
	for (size_t j = 0; j < a; ++j) {
		for (size_t i = 0; i < b; ++i) {
			cur = i * m + j;
			color = getColor(rects, i, j);
			//merge if colors are the same
			if ((i >= 1) && (getColor(rects, i - 1, j) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find((i - 1) * m + j), rectanglesDSU.find(cur));
			}
			if ((i >= 1) && (j >= 1) && (getColor(rects, i - 1, j - 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find((i - 1) * m + j - 1), rectanglesDSU.find(cur));
			}
			if ((j >= 1) && (getColor(rects, i, j - 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find(i * m + j - 1), rectanglesDSU.find(cur));
			}
			if ((j >= 1) && (i + 1 < b) && (getColor(rects, i + 1, j - 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find((i + 1) * m + j - 1), rectanglesDSU.find(cur));
			}
			if ((i + 1 < b) && (getColor(rects, i + 1, j) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find((i + 1) * m + j), rectanglesDSU.find(cur));
			}
			if ((i + 1 < b) && (j + 1 < a) && (getColor(rects, i + 1, j + 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find((i + 1) * m + j + 1), rectanglesDSU.find(cur));
			}
			if ((j + 1 < a) && (getColor(rects, i, j + 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find(i * m + j + 1), rectanglesDSU.find(cur));
			}
			if ((i >= 1) && (j + 1 < a) && (getColor(rects, i - 1, j + 1) == color)) {
				rectanglesDSU.mergeSets(rectanglesDSU.find((i - 1) * m + j + 1), rectanglesDSU.find(cur));
			}
		}
	}
	int s;
	vector<polyArea> rectangleAreas;
	for (size_t i = 0; i < b; ++i) {
		for (size_t j = 0; j < a; ++j) {
			if ((s = rectanglesDSU.get(i * m + j)) < 0) {
				rectangleAreas.push_back({ getColor(rects, i, j), -s });
			}
		}
	}
	sort(rectangleAreas.begin(), rectangleAreas.end(), [](polyArea& area1, polyArea& area2) {
		return (area1.first < area2.first) || ((area1.first == area2.first) && (area1.second < area2.second));
	});
	size_t size = rectangleAreas.size();
	for (size_t i = 0; i < size; ++i) {
		out << rectangleAreas[i].first << ' ' << rectangleAreas[i].second << endl;
	}
	return 0;
}