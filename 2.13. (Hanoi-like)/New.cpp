#include <fstream>
#include <vector>
#pragma comment(linker, "/STACK:67108864")

using namespace std;

struct State {

	short first;
	short second;
	short third;

};

//int stateActions[100][100];

uint32_t countActions(State& s, vector<short>& measures, uint16_t x) {
	int diff = x - s.third;
	if (!diff) {
		return 0;
	}
	if ((s.first == x) || (s.second == x)) {
		return 1 + (s.third != 0);
	}
	if (!(diff % measures[measures.size() - 1]) && (diff > 0)) {
		return 2 * diff / measures[measures.size() - 1];
	}
	short alpha;
	short k;
	uint32_t min = UINT32_MAX;
	uint32_t cur;
	State copyS(s);
	for (size_t i = 0; i < measures.size(); ++i) {
		k = measures[i];
		alpha = -s.third / k;
		while (alpha * k < x) {
			cur = UINT32_MAX;
			s.third = copyS.third + alpha * k;
			s.first = copyS.first - alpha * k;
			if ((s.third >= 0) && (s.first >= 0) && (s.first <= 100) && alpha) {
				//stateActions[s.third][s.first] = 2 * abs(alpha);
				cur = countActions(s, measures, x);
			}
			if (cur < min) {
				min = cur + 2 * abs(alpha);
				if (!(cur % 2) && (alpha < 0)) {
					min -= 1;
				}
			}
			++alpha;
		}
	}
	return min;
}

int main() {
	ios_base::sync_with_stdio(false);
	short x;
	ifstream in("in.txt");
	ofstream out("out.txt");
	State init;
	in >> x >> init.first >> init.second;
	init.third = 100 - init.first - init.second;
	vector<short> measures;
	short temp;
	while (in >> temp) {
		measures.push_back(temp);
	}
	measures.pop_back();
	uint32_t result = 0;
	if (init.third == x) {
		out << 0 << endl;
		return 0;
	}
	if (!measures.size()) {
		out << "No solution" << endl;
		return 0;
	}
	if ((init.first == x) || (init.second == x)) {
		out << 1 + (init.third != 0) << endl;
		return 0;
	}
	if (init.first && init.second) {
		++result;
		init.first += init.second;
		init.second = 0;
	}
	result += countActions(init, measures, x);
	if (result < UINT32_MAX) {
		out << result << endl;
	}
	else {
		out << "No solution" << endl;
	}
	return 0;
}