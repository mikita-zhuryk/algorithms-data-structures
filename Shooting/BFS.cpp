#include <fstream>
#include <vector>
#include <queue>

using namespace std;

typedef pair<uint32_t, uint32_t> vertex;

vector<uint32_t> bfs(vector<vector<uint32_t>>& adjList, vector<vertex>& vertices, uint32_t start, size_t r, size_t c) {
	vector<uint32_t> bfsTree(2 * (c + 1), 0);
	vector<uint32_t> rowShots(r + 1, 0);
	vector<short> visited(2 * (c + 1), 0);
	//bfs with path save
	//need to check whether row of next vertex is empty: if it's empty, that vertex has higher priority (or maybe dinamically add weights 1 and 2 to a graph: 1 - row is empty, 2 - row has at least 1 shot)
	/*auto comp = [&vertices, &rowShots](uint32_t u, uint32_t v) {
		return rowShots[vertices[u].first] == 0 && rowShots[vertices[v].first] != 0;
	};
	vector<uint32_t> container(2 * (c + 1));
	priority_queue<uint32_t, vector<uint32_t>, decltype(comp)> q(comp, container);*/
	queue<uint32_t> q;
	uint32_t lastVertex = start;
	q.push(start);
	visited[start] = true;
	uint32_t u;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		++rowShots[vertices[u].first];
		for (uint32_t v : adjList[u]) {
			if (rowShots[vertices[v].first] == 0) {
				if (!visited[v]) {
					q.push(v);
					if (!bfsTree[v]) {
						bfsTree[v] = u;
					}
					for (uint32_t s : adjList[v]) {
						bfsTree[s] = v;
					}
					visited[v] = true;
				}
			}
		}
		for (uint32_t v : adjList[u]) {
			if (rowShots[vertices[v].first]) {
				if (!visited[v]) {
					q.push(v);
					if (!bfsTree[v]) {
						bfsTree[v] = u;
					}
					visited[v] = true;
				}
			}
		}
		lastVertex = u;
	}
	//something goes wrong when getting path
	vector<uint32_t> path(c);
	path[0] = -1;
	bool allShot = true;
	for (size_t i = 1; i <= r; ++i) {
		if (!rowShots[i]) {
			allShot = false;
			break;
		}
	}
	if (allShot) {
		uint32_t pathRecoveryVertex = (bfsTree[2 * (c + 1) - 1]) ? 2 * (c + 1) - 1 : 2 * (c + 1) - 2;
		size_t counter = c - 1;
		while (pathRecoveryVertex != start) {
			path[counter--] = vertices[pathRecoveryVertex].first;
			pathRecoveryVertex = bfsTree[pathRecoveryVertex];
		}
		path[0] = start;
	}
	return path;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	size_t r;
	size_t c;
	in >> r >> c;
	vector<vector<uint32_t>> adjList(2 * (c + 1));
	vector<vertex> vertices(2 * (c + 1));
	for (size_t i = 1; i <= c; ++i) {
		vertices[2 * i].second = i;
		vertices[2 * i + 1].second = i;
		in >> vertices[2 * i].first >> vertices[2 * i + 1].first;
	}
	for (size_t i = 1; i <= c - 1; ++i) {
		adjList[2 * i].push_back(2 * (i + 1));
		adjList[2 * i].push_back(2 * (i + 1) + 1);
		adjList[2 * i + 1].push_back(2 * (i + 1));
		adjList[2 * i + 1].push_back(2 * (i + 1) + 1);
	}
	auto path = bfs(adjList, vertices, 2, r, c);
	if (path[0] == -1) {
		path = bfs(adjList, vertices, 3, r, c);
		if (path[0] == -1) {
			out << "No\n";
			return 0;
		}
	}
	for (size_t i = 0; i < c; ++i) {
		out << path[i];
		if (i != c - 1) {
			out << ' ';
		}
	}
	out << endl;
	return 0;
}