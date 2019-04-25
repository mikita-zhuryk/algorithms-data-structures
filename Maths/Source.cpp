#include <fstream>
#include <iostream>
#include <ctime>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

typedef pair<short, short> index;

struct BinHeap {

	index* heap;
	size_t n;
	size_t max_n;

	BinHeap(size_t max = 12) {
		max_n = max;
		heap = new index[max_n];
		n = 0;
	}

	void add(index key) {
		if (n + 1 == max_n) {
			max_n *= 2;
			index* temp = new index[max_n];
			for (size_t i = 0; i < n; ++i) {
				temp[i] = heap[i];
			}
			delete[] heap;
			heap = temp;
		}
		heap[++n] = key;
		size_t pos = n;
		while (heap[pos / 2].first < heap[pos].first) {
			swap(heap[pos / 2], heap[pos]);
			pos /= 2;
		}
		if (heap[pos / 2].first == heap[pos].first) {
			while (heap[pos / 2].second > heap[pos].second) {
				swap(heap[pos / 2], heap[pos]);
				pos /= 2;
			}
		}
	}

	index get() {
		return heap[0];
	}

	void remove() {
		heap[0] = heap[n - 1];
		--n;
		size_t pos = 0;
		while (heap[2 * pos + 1].first > heap[pos].first) {
			if (heap[2 * pos + 1].first > heap[2 * pos].first) {
				swap(heap[2 * pos + 1], heap[pos]);
				pos = 2 * pos + 1;
			}
			else {
				swap(heap[2 * pos], heap[pos]);
				pos *= 2;
			}
		}
		if (heap[pos / 2].first == heap[pos].first) {
			while (heap[pos / 2].second < heap[pos].second) {
				swap(heap[pos / 2], heap[pos]);
				pos /= 2;
			}
		}
	}

	size_t find(index key) {
		
	}

	bool isEmpty() {
		return n == 0;
	}

};

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

vector<int> findInput(vector<int>& sums, size_t n) {
	vector<int> result(n);
	result[0] = sums[0] / 2;
	if (n > 1) {
		result[1] = sums[1] - result[0];
	}
	size_t count = 1;
	size_t i = 3;
	index cur;
	/*BinHeap bh;
	bh.add(make_pair(2, 2));
	bh.add(make_pair(1, 3));*/
	/*stack<index> profile;
	stack<index> profileCopy;
	profile.push(make_pair(1, 3));
	profile.push(make_pair(2, 2));*/
	while (i < n*n) {
		/*do {
			cur = bh.get();
			bh.remove();
		} while (!bh.isEmpty() && result[cur.first - 1] + result[cur.second - 1] != sums[i]);*/
		/*do {
			cur = profile.top();
			profile.pop();
			profileCopy.push(cur);
		} while (!profile.empty() && result[cur.first - 1] + result[cur.second - 1] != sums[i]);
		if (cur.first != cur.second) {
			result[cur.second - 1] = sums[i] - result[cur.first - 1];
			if (cur.second + 1 <= n) {
				profile.push(make_pair(cur.first, cur.second + 1));
			}
			if (cur.first + 1 <= n) {
				profile.push(make_pair(cur.first + 1, cur.second));
			}
			i += 2;
		}
		else {
			if (cur.second + 1 <= n) {
				profile.push(make_pair(cur.first, cur.second + 1));
				profile.push(make_pair(cur.second + 1, cur.second + 1));
			}
			++i;
		}
		while (!profileCopy.empty()) {
			cur = profileCopy.top();
			profileCopy.pop();
			profile.push(cur);
		}*/
	}
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
	/*vector<int> sums(n * n);
	for (size_t i = 0; i < n * n; ++i) {
		in >> sums[i];
	}
	auto result = findInput(sums, n);*/


	auto testData = test(n);
	auto input = testData.first;
	auto sums = testData.second;
	auto result = findInput(sums, n);
	size_t count = 0;
	while (checkAnswer(input, result)) {
		testData = test(n);
		input = testData.first;
		sums = testData.second;
		result = findInput(sums, n);
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