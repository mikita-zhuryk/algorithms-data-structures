#include <fstream>
#include <vector>
#include <set>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	uint32_t m;
	in >> n;
	vector<set<uint32_t>> adj(n);
	uint32_t u;
	uint32_t v;
	uint32_t l;
	for (uint32_t u = 0; u < n; ++u) {
		in >> l;
		for (uint32_t i = 0; i < l; ++i) {
			in >> v;
			adj[u - 1].insert(v);
		}
	}
	return 0;
}