#include <fstream>

using namespace std;

int max(int first, int second) {
	return (first > second) ? first : second;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	size_t n = 1;
	in >> n;
	if (n == 2) {
		out << "-1\n";
		return 0;
	}
	int* mosq = new int[n];
	int* lunch = new int[n];
	for (size_t i = 0; i < n; ++i) {
		in >> mosq[i];
	}
	lunch[0] = mosq[0];
	if (n == 1) {
		out << lunch[0] << endl;
		return 0;
	}
	lunch[1] = -1;
	lunch[2] = lunch[0] + mosq[2];
	for (size_t i = 3; i < n; ++i) {
		lunch[i] = max(lunch[i - 3], lunch[i - 2]) + mosq[i];
	}
	out << lunch[n - 1] << endl;
	return 0;
}