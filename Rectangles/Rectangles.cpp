//#include <fstream>
//#include <vector>
//#include <iostream>
//#include <algorithm>
//
//using namespace std;
//
//short a;
//short b;
//
//typedef pair<short, short> point;
//typedef pair<short, int> polyArea;
//
//struct Rectangle {
//
//	point leftLow;
//	point rightHigh;
//	short width;
//	short height;
//	short color;
//
//	Rectangle() {
//		leftLow = make_pair(-1, -1);
//		rightHigh = make_pair(-1, -1);
//		color = 0;
//		calcSides();
//	}
//
//	Rectangle(point leftLow, point rightHigh, short color) {
//		this->leftLow = leftLow;
//		this->rightHigh = rightHigh;
//		this->color = color;
//		calcSides();
//	}
//
//	void calcSides() {
//		width = rightHigh.first - leftLow.first;
//		height = rightHigh.second - leftLow.second;
//	}
//
//	void translate() {
//		leftLow.first += b / 2;
//		rightHigh.first += b / 2 - 1;
//		leftLow.second += a / 2;
//		rightHigh.second += a / 2 - 1;
//	}
//
//	short area() {
//		return height * width;
//	}
//
//	bool contains(point x) {
//		return ((x.first >= leftLow.first) && (x.first <= rightHigh.first)) && ((x.second >= leftLow.second) && (x.second <= rightHigh.second));
//	}
//
//};
//
//struct rectArea {
//
//	uint32_t s;
//	short color;
//
//	rectArea() {
//		s = 0;
//		color = 1;
//	}
//
//	rectArea(uint32_t area, short color) {
//		s = area;
//		this->color = color;
//	}
//
//	rectArea(const rectArea& obj) {
//		s = obj.s;
//		color = obj.color;
//	}
//
//	bool operator<(const rectArea& obj) const {
//		if (color < obj.color) {
//			return true;
//		}
//		else if (color == obj.color) {
//			return s < obj.s;
//		}
//		return false;
//	}
//
//	bool operator==(const rectArea& obj) const {
//		return s == obj.s && color == obj.color;
//	}
//
//	bool operator>(const rectArea& obj) const {
//		return !(*this == obj) && !(*this < obj);
//	}
//
//	rectArea& operator=(const rectArea& obj) {
//		s = obj.s;
//		color = obj.color;
//		return *this;
//	}
//
//};
//
//short getColor(vector<Rectangle>& rects, short x, short y) {
//	for (int i = rects.size() - 1; i >= 0; --i) {
//		if (rects[i].contains(make_pair(x, y))) {
//			return rects[i].color;
//		}
//	}
//}
//
//void drawColors(vector<Rectangle>& rects) {
//	short** colors = new short*[b];
//	for (short i = 0; i < b; ++i) {
//		colors[i] = new short[a];
//		for (short j = 0; j < a; ++j) {
//			colors[i][j] = getColor(rects, i, j);
//		}
//	}
//	for (short j = a - 1; j >= 0; --j) {
//		for (short i = 0; i < b; ++i) {
//			cout << (short)colors[i][j] << ' ';
//		}
//		cout << endl;
//	}
//	for (short i = 0; i < b; ++i) {
//		delete[] colors[i];
//	}
//	delete[] colors;
//}
//
//uint32_t findPolygonArea(vector<Rectangle>& rects, bool** used, short startX, short startY) {
//	uint32_t area = 1;
//	short color = getColor(rects, startX, startY);
//	used[startX][startY] = true;
//	if ((startX >= 1) && !used[startX - 1][startY] && (getColor(rects, startX - 1, startY) == color)) {
//		area += findPolygonArea(rects, used, startX - 1, startY);
//	}
//	if ((startX >= 1) && (startY + 1 < a) && !used[startX - 1][startY + 1] && (getColor(rects, startX - 1, startY + 1) == color)) {
//		area += findPolygonArea(rects, used, startX - 1, startY + 1);
//	}
//	if ((startY + 1 < a) && !used[startX][startY + 1] && (getColor(rects, startX, startY + 1) == color)) {
//		area += findPolygonArea(rects, used, startX, startY + 1);
//	}
//	if ((startX + 1 < b) && (startY + 1 < a) && !used[startX + 1][startY + 1] && (getColor(rects, startX + 1, startY + 1) == color)) {
//		area += findPolygonArea(rects, used, startX + 1, startY + 1);
//	}
//	if ((startX + 1 < b) && !used[startX + 1][startY] && (getColor(rects, startX + 1, startY) == color)) {
//		area += findPolygonArea(rects, used, startX + 1, startY);
//	}
//	if ((startX + 1 < b) && (startY >= 1) && !used[startX + 1][startY - 1] && (getColor(rects, startX + 1, startY - 1) == color)) {
//		area += findPolygonArea(rects, used, startX + 1, startY - 1);
//	}
//	if ((startY >= 1) && !used[startX][startY - 1] && (getColor(rects, startX, startY - 1) == color)) {
//		area += findPolygonArea(rects, used, startX, startY - 1);
//	}
//	if ((startX >= 1) && (startY >= 1) && !used[startX - 1][startY - 1] && (getColor(rects, startX - 1, startY - 1) == color)) {
//		area += findPolygonArea(rects, used, startX - 1, startY - 1);
//	}
//	return area;
//}
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	ifstream in("in.txt");
//	ofstream out("out.txt");
//	short n;
//	in >> a >> b >> n;
//	vector<Rectangle> rects(n + 1);
//	rects[0] = Rectangle(make_pair(-b/2, -a/2), make_pair(b/2, a/2), 1);
//	rects[0].translate();
//	rects[0].calcSides();
//	for (size_t i = 1; i < n + 1; ++i) {
//		in >> rects[i].leftLow.first >> rects[i].leftLow.second;
//		in >> rects[i].rightHigh.first >> rects[i].rightHigh.second;
//		in >> rects[i].color;
//		rects[i].translate();
//		rects[i].calcSides();
//	}
//	bool** used = new bool*[b];
//	for (size_t i = 0; i < b; ++i) {
//		used[i] = new bool[a];
//		for (size_t j = 0; j < a; ++j) {
//			used[i][j] = false;
//		}
//	}
//	uint32_t s = 0;
//	short color;
//	rectArea temp;
//	vector<rectArea> result;
//	for (short i = 0; i < b; ++i) {
//		for (short j = 0; j < a; ++j) {
//			if (!used[i][j]) {
//				s = findPolygonArea(rects, used, i, j);
//				color = getColor(rects, i, j);
//				temp = rectArea(s, color);
//				result.push_back(temp);
//			}
//		}
//	}
//	sort(result.begin(), result.end());
//	for (size_t i = 0; i < result.size(); ++i) {
//		out << result[i].color << ' ' << result[i].s << '\n';
//	}
//	for (size_t i = 0; i < b; ++i) {
//		delete[] used[i];
//	}
//	delete[] used;
//	return 0;
//}