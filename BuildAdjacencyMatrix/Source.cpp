#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint16_t n;
	uint16_t m;
	in >> n >> m;
	uint16_t** adjMatrix = new uint16_t*[n];
	for (size_t i = 0; i < n; ++i) {
		adjMatrix[i] = new uint16_t[n]{ 0 };
	}
	uint16_t u;
	uint16_t v;
	for (size_t i = 0; i < m; ++i) {
		in >> u >> v;
		adjMatrix[u - 1][v - 1] = 1;
		adjMatrix[v - 1][u - 1] = 1;
	}
	for (size_t i = 0; i < n; ++i) {
		for (size_t j = 0; j < n; ++j) {
			out << adjMatrix[i][j];
			if (j != n - 1) {
				out << ' ';
			}
		}
		out << endl;
	}
	return 0;
}