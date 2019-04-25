#include <fstream>
#include <stack>
#include <vector>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	in >> n;
	uint32_t** adjMatrix = new uint32_t*[n + 1];
	for (uint32_t i = 1; i < n + 1; ++i) {
		adjMatrix[i] = new uint32_t[n + 1];
		for (size_t j = 1; j < n + 1; ++j) {
			in >> adjMatrix[i][j];
		}
	}
	uint32_t count = 1;
	uint32_t u;
	stack<uint32_t> st;
	vector<bool> used(n + 1, false);
	vector<uint32_t> labels(n + 1);
	for (uint32_t minUnused = 1; minUnused < n + 1; ++minUnused) {
		st.push(minUnused);
		while (!st.empty()) {
			u = st.top();
			st.pop();
			if (!used[u]) {
				labels[u] = count++;
				for (int j = n; j >= 1; --j) {
					if (!used[j] && adjMatrix[u][j]) {
						st.push(j);
					}
				}
			}
			used[u] = 1;
		}
	}
	for (uint32_t i = 1; i < n + 1; ++i) {
		out << labels[i];
		if (i != n) {
			out << ' ';
		}
	}
	for (uint32_t i = 1; i < n + 1; ++i) {
		delete[] adjMatrix[i];
	}
	delete[] adjMatrix;
	out << endl;
	return 0;
}