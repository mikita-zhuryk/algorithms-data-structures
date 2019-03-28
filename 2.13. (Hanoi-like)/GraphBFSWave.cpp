//#include <fstream>
//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <queue>
//#pragma comment(linker, "/STACK:67108864")
//#define SUM_VOLUME 100
//#define MATRIX_DIM SUM_VOLUME + 1
//
//using namespace std;
//
//typedef uint32_t vertex;
//
//struct State {
//
//	short first;
//	short second;
//	short third;
//
//	State() {
//		first = second = third = 0;
//	}
//
//	State(short f, short s, short t) {
//		first = f;
//		second = s;
//		third = t;
//	}
//
//	bool operator==(const State& s) const {
//		return (first == s.first) && (second == s.second) && (third == s.third);
//	}
//
//};
//
//vector<pair<State, vector<State>>> buildAdjacencyList(State& s, vector<short>& measures) {
//	vector<pair<State, vector<State>>> adj(1);
//	bool used;
//	short measure;
//	queue<State> q;
//	State temp;
//	size_t i = 0;
//	q.push(s);
//	while (!q.empty()) {
//		used = false;
//		temp = q.front();
//		q.pop();
//		for (int i = 0; i < adj.size(); ++i) {
//			if (temp == adj[i].first) {
//				used = true;
//				break;
//			}
//		}
//		if (!used) {
//			adj.push_back(make_pair(temp, vector<State>()));
//			++i;
//			for (int m = measures.size() - 1; m > 0; --m) {
//				measure = measures[m];
//
//				if (temp.second + temp.first <= SUM_VOLUME) adj[i].second.push_back(State(0, temp.second + temp.first, temp.third));
//				if (temp.third + temp.first <= SUM_VOLUME) adj[i].second.push_back(State(0, temp.second, temp.third + temp.first));
//				if (temp.first + temp.second <= SUM_VOLUME) adj[i].second.push_back(State(temp.first + temp.second, 0, temp.third));
//				if (temp.third + temp.second <= SUM_VOLUME) adj[i].second.push_back(State(temp.first, 0, temp.third + temp.second));
//				if (temp.first + temp.third <= SUM_VOLUME) adj[i].second.push_back(State(temp.first + temp.third, temp.second, 0));
//				if (temp.second + temp.third <= SUM_VOLUME) adj[i].second.push_back(State(temp.first, temp.second + temp.third, 0));
//
//				if ((temp.first - (-temp.second + measure) >= 0) && (temp.first - (-temp.second + measure) <= 100) && (temp.second <= measure)) {
//					adj[i].second.push_back(State(temp.first - (measure - temp.second), measure, temp.third));
//				}
//				if ((temp.second - (-temp.first + measure) >= 0) && (temp.second - (-temp.first + measure) <= 100) && (temp.first <= measure)) {
//					adj[i].second.push_back(State(measure, temp.second - (measure - temp.first), temp.third));
//				}
//				if ((temp.third - (-temp.first + measure) >= 0) && (temp.third - (-temp.first + measure) <= 100) && (temp.first <= measure)) {
//					adj[i].second.push_back(State(measure, temp.second, temp.third - (measure - temp.first)));
//				}
//				if ((temp.third - (-temp.second + measure) >= 0) && (temp.third - (-temp.second + measure) <= 100) && (temp.second <= measure)) {
//					adj[i].second.push_back(State(temp.first, measure, temp.third - (measure - temp.second)));
//				}
//			}
//			for (size_t j = 0; j < adj[i].second.size(); ++j) {
//				q.push(adj[i].second[j]);
//			}
//		}
//	}
//	cout << i << endl;
//	return adj;
//}
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	ofstream m("temp1.txt");
//	for (int i = 1; i < 100; ++i) {
//		m << i << ' ';
//	}
//	short x;
//	ifstream in("in.txt");
//	ofstream out("out.txt");
//	State init;
//	in >> x >> init.first >> init.second;
//	init.third = 100 - init.first - init.second;
//	vector<short> measures;
//	short temp;
//	while (in >> temp) {
//		measures.push_back(temp);
//	}
//	buildAdjacencyList(init, measures);
//	system("pause");
//	return 0;
//}