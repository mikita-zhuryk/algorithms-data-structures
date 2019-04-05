//#include <fstream>
//#include <vector>
//#include <algorithm>
////#include <iostream>
////#include <chrono>
//#pragma comment(linker, "/STACK:67108864")
//#define SUM_VOLUME 100
//#define MATRIX_DIM SUM_VOLUME + 1
//
//using namespace std;
////using namespace std::chrono;
//
//struct State {
//
//	short first;
//	short second;
//	short third;
//
//};
//
//uint32_t findMinActions(uint32_t*** stateActions, short x) {
//	uint32_t min = UINT32_MAX;
//	uint32_t cur;
//	for (uint16_t i = 0; i < MATRIX_DIM; ++i) {
//		for (uint16_t j = 0; j < MATRIX_DIM; ++j) {
//			cur = stateActions[i][j][x];
//			if (cur < min) {
//				min = cur;
//			}
//		}
//	}
//	return min;
//}
//
//uint32_t countActions(uint32_t*** stateActions, State& s, vector<short>& measures, uint16_t x) {
//	short measure;
//	uint32_t addition;
//	int k = 0;
//	for (int m = measures.size() - 1; m >= 0; --m) {
//		measure = measures[m];
//		for (int l = 0; l < MATRIX_DIM / measure; ++l) {
//			for (int i = 0; i < MATRIX_DIM; ++i) {
//				for (int j = 0; j < MATRIX_DIM - i; ++j) {
//					k = SUM_VOLUME - i - j;
//					if ((k >= 0) && (stateActions[i][j][k] != UINT32_MAX)) {
//						//перелить всё
//						addition = stateActions[i][j][k] + 1;
//						if (j + i <= SUM_VOLUME) stateActions[0][j + i][k] = min(stateActions[0][j + i][k], addition);
//						if (k + i <= SUM_VOLUME) stateActions[0][j][k + i] = min(stateActions[0][j][k + i], addition);
//						if (i + j <= SUM_VOLUME) stateActions[i + j][0][k] = min(stateActions[i + j][0][k], addition);
//						if (k + j <= SUM_VOLUME) stateActions[i][0][k + j] = min(stateActions[i][0][k + j], addition);
//						if (i + k <= SUM_VOLUME) stateActions[i + k][j][0] = min(stateActions[i + k][j][0], addition);
//						if (j + k <= SUM_VOLUME) stateActions[i][j + k][0] = min(stateActions[i][j + k][0], addition);
//						//долить до деления
//						if ((i - (-j + measure) >= 0) && (i - (-j + measure) <= SUM_VOLUME) && (j <= measure)) {
//							stateActions[i - (-j + measure)][measure][k] = min(addition, stateActions[i - (-j + measure)][measure][k]);
//						}
//						if ((j - (-i + measure) >= 0) && (j - (-i + measure) <= SUM_VOLUME) && (i <= measure)) {
//							stateActions[measure][j - (-i + measure)][k] = min(addition, stateActions[measure][j - (-i + measure)][k]);
//						}
//						if ((k - (-i + measure) >= 0) && (k - (-i + measure) <= SUM_VOLUME) && (i <= measure)) {
//							stateActions[measure][j][k - (-i + measure)] = min(addition, stateActions[measure][j][k - (-i + measure)]);
//						}
//						if ((k - (-j + measure) >= 0) && (k - (-j + measure) <= SUM_VOLUME) && (j <= measure)) {
//							stateActions[i][measure][k - (-j + measure)] = min(addition, stateActions[i][measure][k - (-j + measure)]);
//						}
//					}
//				}
//			}
//		}
//	}
//	return findMinActions(stateActions, x);
//}
//
//int main() {
//	//high_resolution_clock::time_point t1 = high_resolution_clock::now();
//	ios_base::sync_with_stdio(false);
//	short x;
//	ifstream in("in.txt");
//	ofstream out("out.txt");
//	State init;
//	in >> x >> init.first >> init.second;
//	init.third = SUM_VOLUME - init.first - init.second;
//	vector<short> measures;
//	short temp;
//	while (in >> temp) {
//		measures.push_back(temp);
//	}
//	uint32_t*** stateActions = new uint32_t**[MATRIX_DIM];
//	for (uint16_t i = 0; i < MATRIX_DIM; ++i) {
//		stateActions[i] = new uint32_t*[MATRIX_DIM];
//		for (uint16_t j = 0; j < MATRIX_DIM; ++j) {
//			stateActions[i][j] = new uint32_t[MATRIX_DIM];
//			for (uint16_t k = 0; k < MATRIX_DIM; ++k) {
//				stateActions[i][j][k] = UINT32_MAX;
//			}
//		}
//	}
//	stateActions[init.first][init.second][init.third] = 0;
//	measures.pop_back();
//	uint32_t result = countActions(stateActions, init, measures, x);
//	if (result < UINT32_MAX) {
//		out << result << endl;
//	}
//	else {
//		out << "No solution" << endl;
//	}
//	//cout << duration_cast<microseconds>(high_resolution_clock::now() - t1).count();
//	//system("pause");
//	return 0;
//}