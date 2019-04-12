#include <fstream>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>

using namespace std;

pair<vector<int>, vector<int>> test(size_t n) {
	srand(time(NULL));
	vector<int> input(n);
	vector<int> sums;
	for (size_t i = 0; i < n; ++i) {
		input[i] = rand() % 100;
	}
	sort(input.begin(), input.end());
	for (size_t i = 0; i < n; ++i) {
		sums.push_back(2 * input[i]);
		for (size_t j = i + 1; j < n; ++j) {
			sums.push_back(input[i] + input[j]);
			sums.push_back(input[i] + input[j]);
		}
	}
	sort(sums.begin(), sums.end());
	return make_pair(input, sums);
}

vector<int> findInput(vector<int>& sums) {
	vector<int> result;
	return result;
}

bool checkAnswer(vector<int> t, vector<int> p) {
	if (t.size() != p.size()) {
		return false;
	}
	for (size_t i = 0; i < t.size(); ++i) {
		if (t[i] != p[i]) {
			return false;
		}
	}
	return true;
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	size_t n;
	in >> n;


	auto testData = test(n);
	auto input = testData.first;
	auto sums = testData.second;
	auto result = findInput(sums);
	size_t count = 0;
	while (checkAnswer(input, result)) {
		testData = test(n);
		input = testData.first;
		sums = testData.second;
		result = findInput(sums);
		cout << ++count << endl;
	}
	cout << "Input:\n";
	for (size_t i = 0; i < n * n; ++i) {
		cout << sums[i] << ' ';
	}
	cout << endl << "Expected:\n";
	for (size_t i = 0; i < n; ++i) {
		cout << input[i] << ' ';
	}
	cout << endl << "Found:\n";
	for (size_t i = 0; i < n; ++i) {
		cout << result[i] << ' ';
	}
	system("pause");
	return 0;
}