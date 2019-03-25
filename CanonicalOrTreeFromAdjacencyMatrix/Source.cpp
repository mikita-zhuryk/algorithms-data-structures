#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	in >> n;
	uint16_t** adjMatrix = new uint16_t*[n];
	for (uint32_t i = 0; i < n; ++i) {
		adjMatrix[i] = new uint16_t[n]{ 0 };
	}
	for (uint32_t i = 0; i < n; ++i) {
		for (uint32_t j = 0; j < n; ++j) {
			in >> adjMatrix[i][j];
		}
	}
	bool found = false;
	for (uint32_t j = 0; j < n; ++j) {
		found = false;
		for (uint32_t i = 0; i < n; ++i) {
			if (adjMatrix[i][j] == 1) {
				out << i + 1;
				found = true;
				break;
			}
		}
		if (!found) {
			out << 0;
		}
		if (j != n - 1) {
			out << ' ';
		}
	}
	out << endl;
	return 0;
}