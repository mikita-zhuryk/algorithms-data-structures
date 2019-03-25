#include <fstream>
#include <queue>

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
	uint32_t count = 1;
	uint32_t u;
	queue<uint32_t> q;
	uint16_t* used = new uint16_t[n]{ 0 };
	uint32_t* labels = new uint32_t[n];
	uint32_t minUnused = 0;
	while (minUnused != -1) {
		q.push(minUnused + 1);
		used[minUnused] = 1;
		while (!q.empty()) {
			u = q.front();
			q.pop();
			labels[u - 1] = count++;
			for (uint32_t j = 0; j < n; ++j) {
				if (!used[j] && adjMatrix[u - 1][j]) {
					q.push(j + 1);
					used[j] = 1;
				}
			}
		}
		minUnused = -1;
		for (size_t i = 0; i < n; ++i) {
			if (!used[i]) {
				minUnused = i;
				break;
			}
		}
	}
	for (uint32_t i = 0; i < n; ++i) {
		out << labels[i];
		if (i != n - 1) {
			out << ' ';
		}
	}
	out << endl;
	return 0;
}