#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
#pragma comment(linker, "/STACK:67108864")
#define SUM_VOLUME 100
#define MATRIX_DIM SUM_VOLUME + 1

using namespace std;

struct State {

	short first;
	short second;
	short third;

};

uint32_t findMinActions(uint32_t*** stateActions, short x) {
	uint32_t min = UINT32_MAX;
	uint32_t cur;
	ofstream temp("temp.txt");
	for (uint16_t i = 0; i < MATRIX_DIM; ++i) {
		for (uint16_t j = 0; j < MATRIX_DIM; ++j) {
			cur = stateActions[i][j][x];
			if (cur < min) {
				min = cur;
			}
			temp << cur << ' ';
		}
		temp << endl;
	}
	return min;
}

uint32_t countActions(uint32_t*** stateActions, State& s, vector<short>& measures, uint16_t x) {
	short measure;
	int k = 0;
	for (int l = 0; l < SUM_VOLUME; ++l) {
		for (int m = measures.size() - 1; m >= 0; --m) {
			measure = measures[m];
			for (int i = 0; i < MATRIX_DIM; ++i) {
				for (int j = 0; j < MATRIX_DIM; ++j) {
					k = SUM_VOLUME - i - j;
					if ((k >= 0) && (stateActions[i][j][k] != UINT32_MAX)) {
						//перелить всё
						if (j + i <= SUM_VOLUME) stateActions[0][j + i][k] = min(stateActions[0][j + i][k], stateActions[i][j][k] + 1);
						if (k + i <= SUM_VOLUME) stateActions[0][j][k + i] = min(stateActions[0][j][k + i], stateActions[i][j][k] + 1);
						if (i + j <= SUM_VOLUME) stateActions[i + j][0][k] = min(stateActions[i + j][0][k], stateActions[i][j][k] + 1);
						if (k + j <= SUM_VOLUME) stateActions[i][0][k + j] = min(stateActions[i][0][k + j], stateActions[i][j][k] + 1);
						if (i + k <= SUM_VOLUME) stateActions[i + k][j][0] = min(stateActions[i + k][j][0], stateActions[i][j][k] + 1);
						if (j + k <= SUM_VOLUME) stateActions[i][j + k][0] = min(stateActions[i][j + k][0], stateActions[i][j][k] + 1);
						//долить до деления
						if ((i - (-j + measure) >= 0) && (i - (-j + measure) <= SUM_VOLUME) && (j <= measure)) {
							stateActions[i - (-j + measure)][measure][k] = min(stateActions[i][j][k] + 1, stateActions[i - (-j + measure)][measure][k]);
						}
						if ((j - (-i + measure) >= 0) && (j - (-i + measure) <= SUM_VOLUME) && (i <= measure)) {
							stateActions[measure][j - (-i + measure)][k] = min(stateActions[i][j][k] + 1, stateActions[measure][j - (-i + measure)][k]);
						}
						if ((k - (-i + measure) >= 0) && (k - (-i + measure) <= SUM_VOLUME) && (i <= measure)) {
							stateActions[measure][j][k - (-i + measure)] = min(stateActions[i][j][k] + 1, stateActions[measure][j][k - (-i + measure)]);
						}
						if ((k - (-j + measure) >= 0) && (k - (-j + measure) <= SUM_VOLUME) && (j <= measure)) {
							stateActions[i][measure][k - (-j + measure)] = min(stateActions[i][j][k] + 1, stateActions[i][measure][k - (-j + measure)]);
						}
					}
				}
			}
		}
	}
	return findMinActions(stateActions, x);
}

int main() {
	ios_base::sync_with_stdio(false);
	short x;
	ifstream in("in.txt");
	ofstream out("out.txt");
	State init;
	in >> x >> init.first >> init.second;
	init.third = SUM_VOLUME - init.first - init.second;
	vector<short> measures;
	short temp;
	while (in >> temp) {
		measures.push_back(temp);
	}
	uint32_t*** stateActions = new uint32_t**[MATRIX_DIM];
	for (uint16_t i = 0; i < MATRIX_DIM; ++i) {
		stateActions[i] = new uint32_t*[MATRIX_DIM];
		for (uint16_t j = 0; j < MATRIX_DIM; ++j) {
			stateActions[i][j] = new uint32_t[MATRIX_DIM];
			for (uint16_t k = 0; k < MATRIX_DIM; ++k) {
				stateActions[i][j][k] = UINT32_MAX;
			}
		}
	}
	stateActions[init.first][init.second][init.third] = 0;
	measures.pop_back();
	uint32_t result = countActions(stateActions, init, measures, x);
	if (result < UINT32_MAX) {
		out << result << endl;
	}
	else {
		out << "No solution" << endl;
	}
	return 0;
}