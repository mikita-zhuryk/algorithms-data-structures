#include <fstream>
#include <vector>
#include <queue>
#pragma warning(disable: 4996)

typedef std::vector<std::vector<int>> adjList;

int r, c;
std::vector<int> matchingU;
std::vector<int> matchingV;
std::vector<int> distance;

bool bfs(adjList& graph) {
	distance.assign(c + r + 1, INT_MAX);
	std::queue<int> q;
	for (int i = 1; i < c + 1; ++i) {
		if (matchingU[i] == 0) {
			distance[i] = 0;
			q.push(i);
		}
	}
	int u;
	while (!q.empty()) {
		u = q.front();
		q.pop();
		if (distance[u] < distance[0]) {
			for (int i = 0; i < 2; ++i) {
				if (distance[matchingV[graph[u][i] - c]] == INT_MAX) {
					distance[matchingV[graph[u][i] - c]] = distance[u] + 1;
					q.push(matchingV[graph[u][i] - c]);
				}
			}
		}
	}
	return distance[0] != INT_MAX;
}

bool dfs(adjList& graph, int u) {
	if (u != 0) {
		for (int i = 0; i < 2; ++i) {
			if (distance[matchingV[graph[u][i] - c]] == distance[u] + 1 && dfs(graph, matchingV[graph[u][i] - c])) {
				matchingV[graph[u][i] - c] = u;
				matchingU[u] = matchingV[graph[u][i] - c];
				return true;
			}
		}
		distance[u] = INT_MAX;
		return false;
	}
	return true;
}

int HopcroftKarp(adjList& graph) {
	for (int i = 0; i < c + 1; ++i) {
		matchingU[i] = 0;
	}
	for (int i = 0; i < r + 1; ++i) {
		matchingV[i] = 0;
	}
	int matchingCardinality = 0;
	while (bfs(graph)) {
		for (int i = 1; i < c + 1; ++i) {
			if (matchingU[i] == 0 && dfs(graph, i)) {
				++matchingCardinality;
			}
		}
	}
	return matchingCardinality;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	scanf("%d %d", &r, &c);
	adjList graph(r + c + 1, std::vector<int>(2, -1));
	int row1, row2;
	for (int i = 1; i < c + 1; ++i) {
		scanf("%d %d", &row1, &row2);
		graph[i][0] = c + row1;
		graph[i][1] = c + row2;
		graph[c + row1][0] = i;
		graph[c + row2][1] = i;
	}
	matchingU.resize(c + 1);
	matchingV.resize(r + 1);
	matchingU.assign(c + 1, 0);
	matchingV.assign(r + 1, 0);
	distance.resize(r + c + 1);
	int matchingCard = HopcroftKarp(graph);
	if (matchingCard == r) {
		std::vector<int> sequence(c, -1);
		for (int i = 1; i < r + 1; ++i) {
			if (matchingV[i] != 0) {
				sequence[matchingV[i] - 1] = i;
			}
		}
		for (int i = 1; i < c; ++i) {
			if (sequence[i - 1] == -1) {
				printf("%d ", graph[i][0] - c);
			}
			else {
				printf("%d ", sequence[i - 1]);
			}
		}
		if (sequence[c - 1] == -1) {
			printf("%d\n", graph[c][0] - c);
		}
		else {
			printf("%d\n", sequence[c - 1]);
		}
	}
	else {
		printf("No\n");
	}
	return 0;
}