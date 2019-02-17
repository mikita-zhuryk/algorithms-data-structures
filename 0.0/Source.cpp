#include <fstream>
#include <set>
#include <numeric>

using namespace std;

int main() {
	ifstream in("input.txt");
	ofstream out("output.txt");
	long long sum = 0;
	int temp;
	set<int> keys;
	while (in >> temp) {
		keys.insert(temp);
	}
	sum = accumulate(keys.begin(), keys.end(), (long long)0);
	out << sum;
	return 0;
}