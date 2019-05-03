//#include <fstream>
//#include <vector>
//#pragma comment(linker, "/STACK:67108864")
//
//using namespace std;
//
//int goUp(vector<pair<int, int>>& adjList, vector<bool>& leaves, int from, bool print, ofstream& out) {
//	if (adjList[from].first == 0) {
//		if (print) {
//			out << "1 " << from + 1;
//			if (!leaves[from]) {
//				out << ' ';
//			}
//		}
//		return adjList[from].second;
//	}
//	int result = adjList[from].second + goUp(adjList, leaves, adjList[from].first, print, out);
//	if (print) {
//		out << from + 1;
//		if (!leaves[from]) {
//			out << ' ';
//		}
//	}
//	return result;
//}
//
//int main() {
//	ios_base::sync_with_stdio(false);
//	ifstream in("in.txt");
//	ofstream out("out.txt");
//	int n;
//	in >> n;
//	if (n == 1) {
//		out << "0\n1\n";
//		return 0;
//	}
//	vector<pair<int, int>> adjList(n, { -1, -1 });
//	vector<bool> leaves(n, true);
//	int why;
//	int m;
//	int u;
//	int w;
//	for (int i = 0; i < n; ++i) {
//		in >> why >> m;
//		if (m) {
//			leaves[why - 1] = false;
//		}
//		for (int j = 0; j < m; ++j) {
//			in >> u >> w;
//			adjList[u - 1] = { why - 1, w };
//		}
//	}
//	int minIndex;
//	int min = INT_MAX;
//	int cur;
//	for (int i = n - 1; i >= 0; --i) {
//		if (leaves[i]) {
//			cur = goUp(adjList, leaves, i, false, out);
//			if (cur < min) {
//				minIndex = i;
//				min = cur;
//			}
//		}
//	}
//	out << min << endl;
//	goUp(adjList, leaves, minIndex, true, out);
//	return 0;
//}