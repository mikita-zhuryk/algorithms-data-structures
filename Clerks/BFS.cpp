#include <fstream>
#include <vector>
#include <queue>
#include <stack>

using namespace std;

vector<pair<int, int>> bfs(vector<vector<pair<int, int>>>& adjList) {
	int n = adjList.size();
	vector<pair<int, int>> path(n, { 0, 0 });
	path[0] = { -1, 0 };
	queue<int> q;
	q.push(0);
	int u;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		for (auto& uv : adjList[u]) {
			path[uv.first] = { u, uv.second + path[u].second };
			q.push(uv.first);
		}
	}
	return path;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("in.txt");
	ofstream out("out.txt");
	int n;
	in >> n;
	vector<vector<pair<int, int>>> adjList(n);
	vector<bool> leaves(n, true);
	int why;
	int m;
	int u;
	int w;
	for (int i = 0; i < n; ++i) {
		in >> why >> m;
		if (m) {
			leaves[why - 1] = false;
		}
		for (int j = 0; j < m; ++j) {
			in >> u >> w;
			adjList[why - 1].push_back({ u - 1, w });
		}
	}
	vector<pair<int, int>> path = bfs(adjList);
	int minIndex;
	int min;
	for (int i = n - 1; i >= 0; --i) {
		if (leaves[i]) {
			min = path[i].second;
			minIndex = i;
			break;
		}
	}
	int cur;
	for (int i = n - 1; i >= 0; --i) {
		if (leaves[i]) {
			cur = path[i].second;
			if (cur < min) {
				minIndex = i;
				min = cur;
			}
		}
	}
	out << min << endl;
	stack<int> st;
	cur = minIndex;
	while (cur != -1) {
		st.push(cur + 1);
		cur = path[cur].first;
	}
	while (st.size() > 1) {
		out << st.top() << ' ';
		st.pop();
	}
	out << st.top() << endl;
	return 0;
}