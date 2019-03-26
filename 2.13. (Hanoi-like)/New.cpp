#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

struct State {

	short first;
	short second;
	short third;

	short actions;

};

int main() {
	ios_base::sync_with_stdio(false);
	short x;
	ifstream in("in.txt");
	ofstream out("out.txt");
	State init;
	in >> x >> init.first >> init.second;
	init.third = 100 - init.first - init.second;
	init.actions = 0;
	vector<short> measures;
	short temp;
	while (in >> temp) {
		measures.push_back(temp);
	}
	measures.pop_back();
	return 0;
}