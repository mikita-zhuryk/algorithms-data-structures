#include <fstream>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	size_t n = 0;
	in >> n;
	pair<int, int>* matrices = new pair<int, int>[n];
	for (size_t i = 0; i < n; ++i) {
		in >> matrices[i].first >> matrices[i].second;
	}
	int** dp = new int*[n];
	for (size_t i = 0; i < n; ++i) {
		dp[i] = new int[n];
	}
	for (size_t i = 0; i < n; ++i) {
		dp[i][i] = 0;
	}
	int min;
	int cur;
	for (int j = 1; j < n; ++j) {
		for (int i = j - 1; i >= 0; --i) {
			min = INT_MAX;
			for (size_t k = i; k < j; ++k) {
				cur = dp[i][k] + dp[k + 1][j] + matrices[i].first * matrices[k].second * matrices[j].second;
				if (cur < min) {
					min = cur;
				}
			}
			dp[i][j] = min;
		}
	}
	out << dp[0][n - 1] << endl;
	delete[] matrices;
	for (size_t i = 0; i < n; ++i) {
		delete[] dp[i];
	}
	delete[] dp;
	return 0;
}