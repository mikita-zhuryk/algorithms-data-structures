#include <fstream>
#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef pair<short, short> point;

struct Rectangle {
	point leftLow;
	point rightHigh;
	short width;
	short height;
	uint8_t color;

	Rectangle() {
		leftLow = make_pair(0, 0);
		rightHigh = make_pair(0, 0);
		color = 0;
		calcSides();
	}

	Rectangle(point leftLow, point rightHigh, uint8_t color) {
		this->leftLow = leftLow;
		this->rightHigh = rightHigh;
		this->color = color;
		calcSides();
	}

	void translate(short a, short b) {
		leftLow.first += a / 2;
		leftLow.second += b / 2;
		rightHigh.first += a / 2;
		rightHigh.second += b / 2;
	}

	void calcSides() {
		width = rightHigh.first - leftLow.first;
		height = rightHigh.second - leftLow.second;
	}

	short area() {
		return height * width;
	}

};

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("in.txt");
	ofstream out("out.txt");
	short a, b, n;
	in >> a >> b >> n;
	vector<Rectangle> rects(n);
	for (size_t i = 0; i < n; ++i) {
		in >> rects[i].leftLow.first >> rects[i].leftLow.second;
		in >> rects[i].rightHigh.first >> rects[i].rightHigh.second;
		in >> rects[i].color;
		rects[i].translate(a, b);
		rects[i].calcSides();
	}
	system("pause");
	return 0;
}