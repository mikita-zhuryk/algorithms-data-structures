#include <fstream>
#include <stack>

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
	stack<uint32_t> st;
	uint16_t* used = new uint16_t[n]{ 0 };
	uint32_t* labels = new uint32_t[n];
	uint32_t minUnused = 0;
	while (minUnused != -1) {
		st.push(minUnused + 1);
		used[minUnused] = 1;
		while (!st.empty()) {
			u = st.top();
			st.pop();
			labels[u - 1] = count++;
			for (int j = n - 1; j >= 0; --j) {
				if (!used[j] && adjMatrix[u - 1][j]) {
					st.push(j + 1);
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