#include <fstream>
#include <vector>
#include <queue>
#include <iostream>
#pragma comment(linker, "/STACK:67108864")
#define SUM_VOLUME 100

using namespace std;

typedef uint32_t vertex;

struct State {

	short first;
	short second;
	short third;
	uint32_t actions;

	State() {
		first = second = third = 0;
		actions = UINT32_MAX;
	}

	State(short f, short s, short t, uint32_t ac) {
		first = f;
		second = s;
		third = t;
		actions = ac;
	}

};

uint32_t hashState(State& s) {
	return s.first * pow(SUM_VOLUME, 2) + s.second * SUM_VOLUME + s.third;
}

uint32_t waveBFS(State& s, vector<short>& measures, short x) {
	short measure;
	queue<State> q;
	size_t size = pow(SUM_VOLUME, 3) + 1;
	bool* visited = new bool[size];
	for (size_t i = 0; i < size; ++i) {
		visited[i] = false;
	}
	State temp;
	size_t i = 0;
	q.push(s);
	while (!q.empty()) {
		temp = q.front();
		q.pop();
		if (!visited[hashState(temp)]) {
			//cout << temp.first << ' ' << temp.second << ' ' << temp.third << ' ' << temp.actions << endl;
			if (temp.third == x) {
				delete[] visited;
				return temp.actions;
			}
			q.push(State(0, temp.second + temp.first, temp.third, temp.actions + 1));
			q.push(State(0, temp.second, temp.third + temp.first, temp.actions + 1));
			q.push(State(temp.first + temp.second, 0, temp.third, temp.actions + 1));
			q.push(State(temp.first, 0, temp.third + temp.second, temp.actions + 1));
			q.push(State(temp.first + temp.third, temp.second, 0, temp.actions + 1));
			q.push(State(temp.first, temp.second + temp.third, 0, temp.actions + 1));
			for (int m = 0; m < measures.size(); ++m) {
				measure = measures[m];

				if (temp.first > measure) {
					q.push(State(measure, temp.second + (temp.first - measure), temp.third, temp.actions + 1));
					q.push(State(measure, temp.second, temp.third + (temp.first - measure), temp.actions + 1));
				}
				if (temp.second > measure) {
					q.push(State(temp.first + (temp.second - measure), measure, temp.third, temp.actions + 1));
					q.push(State(temp.first, measure, temp.third + (temp.second - measure), temp.actions + 1));
				}

				if ((temp.first - (measure - temp.second) > 0) && (temp.second < measure)) {
					q.push(State(temp.first - (measure - temp.second), measure, temp.third, temp.actions + 1));
				}
				if ((temp.second - (measure - temp.first) > 0) && (temp.first < measure)) {
					q.push(State(measure, temp.second - (measure - temp.first), temp.third, temp.actions + 1));
				}
				if ((temp.third - (measure - temp.first) > 0) && (temp.first < measure)) {
					q.push(State(measure, temp.second, temp.third - (measure - temp.first), temp.actions + 1));
				}
				if ((temp.third - (measure - temp.second) > 0) && (temp.second < measure)) {
					q.push(State(temp.first, measure, temp.third - (measure - temp.second), temp.actions + 1));
				}
			}
			visited[hashState(temp)] = true;
		}
	}
	//cout << temp.first << ' ' << temp.second << ' ' << temp.third << ' ' << temp.actions << endl;
	delete[] visited;
	return UINT32_MAX;
}

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
	uint32_t result = waveBFS(init, measures, x);
	if (result == UINT32_MAX) {
		out << "No solution\n";
	}
	else {
		out << result << endl;
	}
	//system("pause");
	return 0;
}