#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	in >> n;
	uint32_t** adjMatrix = new uint32_t*[n];
	for (uint32_t i = 0; i < n; ++i) {
		adjMatrix[i] = new uint32_t[n];
		for (size_t j = 0; j < n; ++j) {
			in >> adjMatrix[i][j];
		}
	}
}