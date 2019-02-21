#include <fstream>
#include <string>
#include <vector>
#include <ctime>

void fillTXT(std::string path, std::size_t n) {
	srand(time(NULL));
	std::ofstream out(path);
	std::vector<int> numbers;
	for (size_t i = 0; i < n; ++i) {
		numbers.push_back(rand() % 1000);
	}
	out << numbers[rand() % numbers.size()] << "\n" << "\n";
	for (size_t i = 0; i < n; ++i) {
		out << numbers[i] << "\n";
	}
}