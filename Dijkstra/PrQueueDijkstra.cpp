#include <fstream>
#include <queue>

using namespace std;

typedef pair<uint32_t, uint32_t> edge;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	uint32_t m;
	in >> n >> m;
	vector<vector<edge>> adj(n);
	uint32_t u;
	uint32_t v;
	uint32_t w;
	for (uint32_t i = 0; i < m; ++i) {
		in >> u >> v >> w;
		adj[u - 1].push_back(edge(v, w));
	}
	uint64_t* paths = new uint64_t[n];
	for (uint32_t i = 0; i < n; ++i) {
		paths[i] = INT_MAX;
	}
	auto comp = [&paths](uint32_t a, uint32_t b) { return paths[a - 1] < paths[b - 1]; };
	priority_queue<uint32_t, vector<uint32_t>, decltype(comp)> q(comp, vector<uint32_t>(0));
	paths[0] = 0;
	q.push(1);
	while (!q.empty()) {
		u = q.top();
		q.pop();
		for (auto v : adj[u - 1]) {
			if (paths[v.first - 1] > paths[u - 1] + v.second) {
				paths[v.first - 1] = paths[u - 1] + v.second;
				q.push(v.first);
			}
		}
	}
	out << paths[n - 1] << endl;
	return 0;
}