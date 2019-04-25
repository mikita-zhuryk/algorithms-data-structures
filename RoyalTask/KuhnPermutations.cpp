#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, short> edge;


void dfsOrder(vector<vector<edge>>& adjList, int v, vector<bool>& visited, vector<int>& order) {
	visited[v] = true;
	for (edge uv : adjList[v]) {
		if ((uv.second == 1) && !visited[uv.first]) {
			dfsOrder(adjList, uv.first, visited, order);
		}
	}
	order.push_back(v);
}

void dfsComp(vector<vector<edge>>& adjList, int v, vector<bool>& visited, vector<int>& comp) {
	visited[v] = true;
	comp.push_back(v);
	for (edge uv : adjList[v]) {
		if ((uv.second == 1) && !visited[uv.first]) {
			dfsComp(adjList, uv.first, visited, comp);
		}
	}
}

vector<vector<int>> kosaraju(vector<vector<edge>>& adjList, vector<int>& matching) {
	vector<vector<edge>> inverseAdjList(adjList.size());
	vector<bool> visited(adjList.size());
	for (size_t i = 0; i < visited.size(); ++i) {
		visited[i] = false;
	}
	vector<int> order;
	for (size_t i = 0; i < adjList.size(); ++i) {
		for (size_t j = 0; j < adjList[i].size(); ++j) {
			inverseAdjList[adjList[i][j].first].push_back(make_pair(i, adjList[i][j].second));
		}
	}
	for (size_t i = 0; i < adjList.size() / 2; ++i) {
		if (!visited[i]) {
			dfsOrder(inverseAdjList, i, visited, order);
		}
	}
	for (size_t i = 0; i < visited.size(); ++i) {
		visited[i] = false;
	}
	vector<int> comp;
	vector<vector<int>> components;
	for (size_t i = 0; i < adjList.size() / 2; ++i) {
		dfsComp(adjList, i, visited, comp);
		//if two guys are in one component, they share girls
		components.push_back(comp);
		comp.clear();
		comp.resize(0);
		/*for (size_t j = adjList.size() / 2; j < visited.size(); ++j) {
			if (!binary_search(matching.begin(), matching.end(), j)) {
				visited[j] = false;
			}
		}*/
	}
	return components;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("king.in");
	ofstream out("king.out");
	int n;
	int m;
	in >> n;
	vector<vector<edge>> adj(2 * n);
	int v;
	int l;
	for (int u = 0; u < n; ++u) {
		in >> l;
		for (int i = 0; i < l; ++i) {
			in >> v;
			adj[u].push_back(make_pair(n + v - 1, 1));
			adj[n + v - 1].push_back(make_pair(u, -1));
		}
	}
	vector<int> matching(n);
	for (int i = 0; i < n; ++i) {
		in >> matching[i];
		matching[i] += n - 1;
		for (edge& uv : adj[i]) {
			if (uv.first == matching[i]) {
				uv.second = -uv.second;
				for (edge& vu : adj[uv.first]) {
					if (vu.first == i) {
						vu.second = -vu.second;
					}
				}
			}
		}
	}
	auto components = kosaraju(adj, matching);
	size_t j = 0;
	for (auto& component : components) {
		out << component.size() - 1 << ' ';
		j = 0;
		sort(component.begin(), component.end());
		for (size_t i = 1; i < component.size(); ++i) {
			/*if (component[i] >= n) {
				component[i] = component[i] - n + 1;
			}*/
			out << component[i] + 1;
			if (i != component.size() - 1) {
				out << ' ';
			}
		}
		out << endl;
	}
	return 0;
}