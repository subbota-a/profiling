#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;

vector<int> generateInputVector() {
	vector<int> nums;

	// Добавляем числа, повторяющиеся трижды
	for (int i = 1; i <= 30000; ++i) {
		nums.push_back(i);
		nums.push_back(i);
		nums.push_back(i);
	}

	// Добавляем уникальное число, которое встречается только один раз
	nums.push_back(50001);

	// Перемешиваем вектор, чтобы порядок чисел не был очевидным
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(nums.begin(), nums.end(), g);

	return nums;
}

int main() {
	vector<int> nums = generateInputVector();

	// Печатаем вектор для демонстрации
	for (int num : nums) {
		cout << num << ", ";
	}

	return 0;
}
