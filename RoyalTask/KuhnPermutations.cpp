#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;


void dfsOrder(vector<vector<int>>& adjList, int v, vector<bool>& visited, vector<int>& order) {
	visited[v] = true;
	for (int u : adjList[v]) {
		if (!visited[u]) {
			dfsOrder(adjList, u, visited, order);
		}
	}
	order.push_back(v);
}

void dfsComp(vector<vector<int>>& adjList, int v, vector<bool>& visited, vector<int>& comp) {
	visited[v] = true;
	comp.push_back(v);
	for (int u : adjList[v]) {
		if (!visited[u]) {
			dfsComp(adjList, u, visited, comp);
		}
	}
}

vector<vector<int>> kosaraju(vector<vector<int>>& adjList) {
	vector<vector<int>> inverseAdjList(adjList.size());
	vector<bool> visited(adjList.size());
	for (size_t i = 0; i < visited.size(); ++i) {
		visited[i] = false;
	}
	vector<int> order;
	for (size_t i = 0; i < adjList.size(); ++i) {
		for (size_t j = 0; j < adjList[i].size(); ++j) {
			inverseAdjList[adjList[i][j]].push_back(i);
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
	for (int i = order.size() - 1; i >= 0; --i) {
		if (!visited[order[i]]) {
			dfsComp(adjList, order[i], visited, comp);
			components.push_back(comp);
			comp.clear();
		}
	}
	return components;
}

vector<int> intersect(vector<int>& v1, vector<int>& v2) {
	sort(v1.begin(), v1.end());
	sort(v2.begin(), v2.end());
	vector<int> result;
	size_t i = 0;
	size_t j = 0;
	while ((i < v1.size()) && (j < v2.size())) {
		if (v1[i] == v2[j]) {
			result.push_back(v1[i]);
			++i;
			++j;
		}
		else if (v1[i] < v2[j]) {
			++i;
		}
		else {
			++j;
		}
	}
	return result;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("king.in");
	ofstream out("king.out");
	int n;
	int m;
	in >> n;
	vector<vector<int>> adj(2 * n);
	int v;
	int l;
	for (int u = 0; u < n; ++u) {
		in >> l;
		for (int i = 0; i < l; ++i) {
			in >> v;
			adj[u].push_back(n + v - 1);
		}
	}
	vector<vector<int>> adjCopy = adj;
	vector<int> matching(n);
	for (int i = 0; i < n; ++i) {
		in >> matching[i];
		matching[i] += n - 1;
		adj[matching[i]].push_back(i);
		for (auto it = adj[i].begin(); it != adj[i].end(); ++it) {
			if (*it == matching[i]) {
				swap(*it, adj[i][adj[i].size() - 1]);
				adj[i].resize(adj[i].size() - 1);
				break;
			}
		}
	}
	auto components = kosaraju(adj);
	vector<int> table(n);
	for (size_t i = 0; i < n; ++i) {
		table[i] = -1;
	}
	for (size_t i = 0; i < components.size(); ++i) {
		for (size_t j = 0; j < components[i].size(); ++j) {
			if ((components[i][j] < n) && (table[components[i][j]] == -1) && (components[i].size() > 1)) {
				table[components[i][j]] = i;
			}
		}
	}
	vector<int> inter;
	size_t lessThanN;
	for (size_t i = 0; i < n; ++i) {
		lessThanN = 0;
		if (table[i] != -1) {
			for (size_t j = 0; j < components[table[i]].size(); ++j) {
				if (components[table[i]][j] < n) {
					++lessThanN;
				}
			}
		}
		if ((table[i] == -1) || (lessThanN == 1)) {
			out << 1 << ' ' << matching[i] - n + 1 << endl;
		}
		else {
			inter = intersect(components[table[i]], adjCopy[i]);
			out << inter.size() << ' ';
			for (size_t j = 0; j < inter.size(); ++j) {
				out << inter[j] - n + 1;
				if (j != inter.size() - 1) {
					out << ' ';
				}
			}
			out << endl;
		}
	}
	return 0;
}