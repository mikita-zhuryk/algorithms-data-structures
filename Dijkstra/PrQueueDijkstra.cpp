#include <fstream>
#include <queue>
#pragma warning(disable: 4996)

using namespace std;

typedef pair<uint32_t, uint32_t> edge;

typedef pair<uint32_t, int64_t> vertex;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	uint32_t n;
	uint32_t m;
	scanf("%d %d", &n, &m);
	vector<vector<edge>> adj(n + 1);
	uint32_t u;
	uint32_t v;
	uint32_t w;
	uint32_t j;
	bool found;
	for (uint32_t i = 0; i < m; ++i) {
		scanf("%d %d %d", &u, &v, &w);
		found = false;
		if (u != v) {
			adj[u].push_back(edge(v, w));
			adj[v].push_back(edge(u, w));
		}
	}
	vector<int64_t> d(n + 1, INT64_MAX);
	auto comp = [](vertex u, vertex v) { return u.second > v.second; };
	priority_queue<vertex, vector<vertex>, decltype(comp)> q(comp, vector<vertex>(0));
	size_t size;
	q.push({ 1, 0 });
	vertex cur;
	while (!q.empty()) {
		cur = q.top();
		q.pop();
		if (d[cur.first] > cur.second) {
			d[cur.first] = cur.second;
			size = adj[cur.first].size();
			for (size_t i = 0; i < size; ++i) {
				q.push({ adj[cur.first][i].first, min(d[cur.first] + adj[cur.first][i].second, d[adj[cur.first][i].first]) });
			}
		}
	}
	printf("%I64d\n", d[n]);
	return 0;
}