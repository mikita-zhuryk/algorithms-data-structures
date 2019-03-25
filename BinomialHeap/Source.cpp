#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint64_t n;
	in >> n;
	uint16_t count = 0;
	while (n) {
		if (n % 2) {
			out << count << endl;
		}
		n >>= 1;
		++count;
	}
	return 0;
}