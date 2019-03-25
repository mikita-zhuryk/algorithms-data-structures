#include <fstream>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	uint32_t m;
	in >> n >> m;
	vector<vector<uint32_t>> adj(n);
	uint32_t u;
	uint32_t v;
	for (uint32_t i = 0; i < m; ++i) {
		in >> u >> v;
		adj[u - 1].push_back(v);
		adj[v - 1].push_back(u);
	}
	uint32_t l;
	for (uint32_t i = 0; i < n; ++i) {
		l = adj[i].size();
		out << l;
		if (l != 0) {
			out << ' ';
		}
		for (uint32_t j = 0; j < l; ++j) {
			out << adj[i][j];
			if (j != l - 1) {
				out << ' ';
			}
		}
		out << '\n';
	}
	return 0;
}