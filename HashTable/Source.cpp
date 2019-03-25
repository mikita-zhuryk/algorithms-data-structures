#include <fstream>
#include <iostream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	uint16_t m;
	uint16_t c;
	uint16_t n;
	in >> m >> c >> n;
	int32_t* table = new int32_t[m];
	for (uint16_t i = 0; i < m; ++i) {
		table[i] = -1;
	}
	int32_t k;
	uint16_t attempt;
	uint16_t index;
	for (uint16_t i = 0; i < n; ++i) {
		in >> k;
		attempt = 0;
		if (find(table, table + m, k) == table + m) {
			index = ((k % m) + c * attempt++) % m;
			while (table[index] != -1) {
				index = ((k % m) + c * attempt++) % m;
			}
			table[index] = k;
		}
	}
	for (uint16_t i = 0; i < m; ++i) {
		out << table[i];
		if (i != m - 1) {
			out << ' ';
		}
	}
	out << endl;
	delete[] table;
	return 0;
}