#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint32_t n;
	in >> n;
	uint32_t* parents = new uint32_t[n]{ 0 };
	uint32_t u;
	uint32_t v;
	for (uint32_t i = 0; i < n - 1; ++i) {
		in >> u >> v;
		parents[v - 1] = u;
	}
	for (uint32_t i = 0; i < n; ++i) {
		out << parents[i];
		if (i != n - 1) {
			out << ' ';
		}
	}
	out << endl;
	return 0;
}