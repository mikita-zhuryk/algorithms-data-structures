#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	size_t n = 0;
	in >> n;
	
	return 0;
}