#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	size_t n;
	in >> n;
	if (n == 1) {
		out << "Yes\n";
		return 0;
	}
	++n;
	int* keys = new int[n];
	for (size_t i = 1; i < n; ++i) {
		in >> keys[i];
	}
	for (size_t i = 1; i < (n + 1) / 2; ++i) {
		if (((2 * i + 1 < n) && (keys[2 * i + 1] < keys[i])) || (keys[2 * i] < keys[i])) {
			out << "No\n";
			return 0;
		}
	}
	out << "Yes\n";
	return 0;
}