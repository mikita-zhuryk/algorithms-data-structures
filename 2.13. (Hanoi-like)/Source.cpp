//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <iomanip>
//#include <algorithm>
//
//using namespace std;
//
//struct State {
//
//	short first;
//	short second;
//	short third;
//
//	short actions;
//
//};
//
//void printMatrix(vector<vector<short>>& m) {
//	for (size_t i = 0; i < m.size(); ++i) {
//		for (size_t j = 0; j < m[i].size(); ++j) {
//			cout << setw(4) << m[i][j] << ' ';
//		}
//		cout << endl;
//	}
//}
//
//short measureX(State& s, short x, vector<short>& measures) {
//	if (x <= 0) {
//		return 0;
//	}
	//if (s.third == x) {
	//	return 0;
	//}
//	if (binary_search(measures.begin(), measures.end(), x)) {
//		return 2;
//	}
	//if (s.first && s.second) {
	//	++s.actions;
	//	s.first += s.second;
	//	s.second = 0;
	//}
//	size_t m = measures.size();
//	vector<vector<short>> summary(m);
//	size_t max_length = 1 + x / measures[0];
//	for (size_t i = 0; i < m; ++i) {
//		summary[i] = vector<short>(max_length);
//	}
//	size_t l = 0;
//	short measure = 0;
//	for (size_t i = 0; i < m; ++i) {
//		measure = measures[i];
//		l = 1 + x / measure;
//		for (size_t j = 0; j < l; ++j) {
//			summary[i][j] = j * measure;
//		}
//		for (size_t j = l; j < max_length; ++j) {
//			summary[i][j] = -1;
//		}
//	}
//	printMatrix(summary);
//	return -1;
//}
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	short x;
//	ifstream in("in.txt");
//	ofstream out("out.txt");
//	State init;
//	in >> x >> init.first >> init.second;
//	init.third = 100 - init.first - init.second;
//	init.actions = 0;
//	vector<short> measures;
//	short temp;
//	while (in >> temp) {
//		measures.push_back(temp);
//	}
//	measures.pop_back();
//	if (x > 100) {
//		out << "No solution";
//	}
//	else {
//		out << measureX(init, x, measures);
//	}
//	system("pause");
//	return 0;
//}