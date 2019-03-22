#include <fstream>
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#pragma comment(linker, "/STACK:8388608")

using namespace std;

struct Cell {
	short value;
	char dir = 'c';
};

void printMatrix(vector<vector<Cell>>&);

void printAngle(string**, size_t);

char* trim_zeros(char*& s, size_t& size) {
	size_t i = 0;
	while ((s[i] == '0') && (size > 1)) {
		s++;
		--size;
	}
	return s;
}

char* find_common_start(char*& s1, size_t& size1, char*& s2, size_t& size2) {
	size_t size_big = (size1 > size2) ? size1 : size2;
	char* res = new char[size_big + 1];
	res[size_big] = '\0';
	size_t i = 0;
	while ((s1[0] == s2[0]) && size1 && size2) {
		res[i++] = s1[0];
		s1++;
		s2++;
		size1--;
		size2--;
	}
	res[i] = '\0';
	return res;
}

int compare_bin(string& s1, string& s2) {
	for (size_t i = 0; i < s1.size(); ++i) {
		if (s1[i] - s2[i] < 0) {
			return -1;
		}
		if (s1[i] - s2[i] > 0) {
			return 1;
		}
	}
	return 0;
}

vector<vector<Cell>> find_CS_lengths(char* big, size_t& size_big, char* small, size_t& size_small, size_t& result_size) {
	size_t m = size_small + 2;
	size_t n = size_big + 2;
	size_t max_size = (m > n) ? size_small : size_big;
	string** angle = new string*[2];
	angle[0] = new string[n - 1];
	angle[1] = new string[n - 1];
	vector<vector<Cell>> cs_lengths = vector<vector<Cell>>(m);
	for (size_t i = 0; i < m; ++i) {
		cs_lengths[i] = vector<Cell>(n);
	}
	if ((size_big == 0) || (size_small == 0)) {
		result_size = 0;
	}
	else {
		cs_lengths[0][1].value = -1;
		cs_lengths[1][0].value = -1;
		for (size_t i = 2; i < n; ++i) {
			cs_lengths[0][i].value = big[i - 2] - '0';
		}
		for (size_t i = 2; i < m; ++i) {
			cs_lengths[i][0].value = small[i - 2] - '0';
		}
		for (size_t i = 1; i < n; ++i) {
			cs_lengths[1][i].value = 0;
			angle[0][i - 1] = "";
			angle[1][i - 1] = "";
		}
		for (size_t i = 2; i < m; ++i) {
			cs_lengths[i][1].value = 0;
		}
		for (size_t i = 2; i < m; ++i) {
			for (size_t j = 2; j < n; ++j) {
				if (small[i - 2] == big[j - 2]) {
					cs_lengths[i][j].value = cs_lengths[i - 1][j - 1].value + 1;
					cs_lengths[i][j].dir = 'i';
					angle[1][j - 1] = angle[0][j - 2] + small[i - 2];
				}
				else if (cs_lengths[i - 1][j].value > cs_lengths[i][j - 1].value) {
						cs_lengths[i][j].value = cs_lengths[i - 1][j].value;
						cs_lengths[i][j].dir = 'u';
						angle[1][j - 1] = angle[0][j - 1];
				}
				else if (cs_lengths[i][j - 1].value > cs_lengths[i - 1][j].value) {
						cs_lengths[i][j].value = cs_lengths[i][j - 1].value;
						cs_lengths[i][j].dir = 'l';
						angle[1][j - 1] = angle[1][j - 2];
				}
				else {
					cs_lengths[i][j].value = cs_lengths[i - 1][j].value;
					if (compare_bin(angle[0][j - 1], angle[1][j - 2]) > 0) {
						cs_lengths[i][j].dir = 'u';
						angle[1][j - 1] = angle[0][j - 1];
					}
					else {
						cs_lengths[i][j].dir = 'l';
						angle[1][j - 1] = angle[1][j - 2];
					}
				}
			}
			//cout << i << endl;
			//printAngle(angle, n - 1);
			swap(angle[0], angle[1]);
		}
		result_size = cs_lengths[m - 1][n - 1].value;
		//printMatrix(cs_lengths);
	}
	return cs_lengths;
}

char* find_biggest_LCS(vector<vector<Cell>>& cs_lengths) {
	size_t m = cs_lengths.size();
	size_t n = cs_lengths[0].size();
	size_t result_size = cs_lengths[m - 1][n - 1].value;
	char* result = new char[result_size + 1];
	result[result_size] = '\0';
	size_t count = 0;
	size_t j = n - 1;
	size_t i = m - 1;
	while (count < result_size) {
		if (cs_lengths[i][j].dir == 'i') {
			result[result_size - 1 - count] = cs_lengths[i][0].value + '0';
			//cout << "i: " << i << " j: " << j << ' ' << cs_lengths[i][0].value << endl;
			++count;
			--i;
			--j;
		}
		else if (cs_lengths[i][j].dir == 'l') {
			--j;
		}
		else if (cs_lengths[i][j].dir == 'u') {
			--i;
		}
		else {
			break;
		}
	}
	return result;
}

void print(char* result, ofstream& out) {
	size_t i = 0;
	while ((result[i] == '0') || (result[i] == '1')) {
		i++;
	}
	out << i << endl;
	i = 0;
	while ((result[i] == '0') || (result[i] == '1')) {
		out << result[i];
		i++;
	}
}

void printAngle(string** angle, size_t n) {
	for (size_t i = 0; i < 2; ++i) {
		for (size_t j = 0; j < n; ++j) {
			cout << angle[i][j] << ' ';
		}
		cout << endl;
	}
	cout << endl;
}

void printMatrix(vector<vector<Cell>>& m) {
	for (size_t i = 0; i < m.size(); ++i) {
		for (size_t j = 0; j < m[0].size(); ++j) {
			//cout << setw(3) << m[i][j].value << ' ' << setw(1) << m[i][j].dir << ' ' << setw(10) << m[i][j].str << ' ';
			cout << setw(3) << m[i][j].value << ' ' << setw(1) << m[i][j].dir << ' ';
		}
		cout << endl;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	ifstream in("input.txt");
	ofstream out("output.txt");
	size_t size1;
	size_t size2;
	in >> size1 >> size2;
	char* s1 = new char[size1 + 1];
	char* s2 = new char[size2 + 1];
	in >> s1 >> s2;
	size_t max_size = (size1 > size2) ? size1 : size2;
	char* result = new char[max_size + 1];
	char* cur;
	size_t count = 0;
	result[max_size] = '\0';
	trim_zeros(s1, size1);
	trim_zeros(s2, size2);
	cur = find_common_start(s1, size1, s2, size2);
	for (size_t i = 0; i < strlen(cur); ++i) {
		result[count++] = cur[i];
	}
	if (s2[0] == '1') {
		swap(s1, s2);
		swap(size1, size2);
	}
	size_t result_size = 0;
	vector<vector<Cell>> cs_lengths = find_CS_lengths(s1, size1, s2, size2, result_size);
	if (result_size) {
		char* LCS = find_biggest_LCS(cs_lengths);
		for (size_t i = 0; i < result_size; ++i) {
			result[count++] = LCS[i];
		}
	}
	print(result, out);
	//system("pause");
	return 0;
}