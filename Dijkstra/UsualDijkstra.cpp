#include <fstream>
#include <vector>

using namespace std;

typedef uint32_t weight;
typedef uint32_t vertex;
typedef uint64_t path;
typedef pair<vertex, weight> edge;

uint32_t min(uint32_t a, uint32_t b) {
	return (a > b) ? b : a;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	uint32_t m;
	in >> n >> m;
	vector<vector<edge>> adj(n);
	vertex u;
	vertex v;
	weight w;
	for (uint32_t i = 0; i < m; ++i) {
		in >> u >> v >> w;
		adj[u - 1].push_back(edge(v, w));
	}
	path* paths = new path[n];
	vertex* used = new vertex[n];
	for (vertex i = 0; i < n; ++i) {
		used[i] = 0;
		paths[i] = INT_MAX;
	}
	u = 0;
	paths[0] = 0;
	vertex minPathVertex = n;
	path minPath;
	for (uint32_t i = 0; i < n; ++i) {
		minPath = INT_MAX;
		minPathVertex = -1;
		for (vertex j = 0; j < n; ++j) {
			if (!used[j] && paths[j] < minPath) {
				minPathVertex = j;
				minPath = paths[j];
			}
		}
		for (edge uv : adj[minPathVertex]) {
			if (paths[uv.first - 1] > minPath + uv.second) {
				paths[uv.first - 1] = minPath + uv.second;
			}
		}
		used[minPathVertex] = 1;
	}
	out << paths[n - 1] << '\n';
	return 0;
}