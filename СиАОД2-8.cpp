#include <iostream>
#include <vector>
#include <Windows.h>
#include <algorithm>

using namespace std;

void BruteForceChange(int money, int count, vector<int>array) {

	int money1 = money, count1 = 0;
	vector<int> mas;

	sort(array.begin(), array.end(), greater<>());

	for (auto i = array.begin(); i != array.end(); i++) {

		mas.resize(array.end()-i);

		copy(i, array.end(), mas.begin());

		for (int coin : mas) {

			if (money1 / coin != 0) {
				count1 += money1 / coin;
				money1 -= (money1 / coin) * coin;
			}
		}

		if (count1 < count && money1 == 0)
			count = count1;

		money1 = money;
		count1 = 0;
	}

	cout << count;
}

void greedyCoinChange(vector<int>& array, int money) {
	vector<int> result;

	// Сортируем монеты по убыванию
	sort(array.rbegin(), array.rend());

	for (int coin : array) {
		while (money >= coin) {
			result.push_back(coin);
			money -= coin;
		}
	}

	for (int i = 0; i < result.size(); i++)
		cout << result[i] << " ";
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int count, money, n;
	vector<int> array;
	array.push_back(1);

	cout << "Вводите номинал монет. Если ввели все номиналы, введите 0" << endl;
	cin >> count;
	while (count != 0) {
		array.push_back(count);
		cin >> count;
	}

	count = INT_MAX;

	cout << "Введите сумму: ";
	cin >> money;

	cout << "Выберите алгоритм: 1-Грубый перебор; 2-Жадный алгоритм " << endl;
	cin >> n;
	if (n == 1)
		BruteForceChange(money, count, array);
	else
		greedyCoinChange(array, money);

	return 0;
}