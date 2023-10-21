#include<iostream>
#include<vector>
#include<Windows.h>
#include<string>
#include <sstream>
#include <map>

using namespace std;

void createArray(){
	vector <string> array;
	string sentences;
	cout << "Введите предложение." << endl;
	getline(cin, sentences);

	string word;

	istringstream ss(sentences);//Разбиваем предложение на слова

	while (ss >> word) {
		//Удаляем из слов знаки припенания
		if (word[word.length()-1] == '.' || word[word.length()-1] == ',' || word[word.length()-1] == ':' 
			|| word[word.length()-1] == ';'|| word[word.length()-1] == '!' || word[word.length()-1] == '?')
			word.erase(word.length()-1, word.length());

		array.push_back(word);
	}
	//Выводим массив
	for (string i : array)
		cout << i << endl;
}

bool findArray(char s, vector<char> array) {
	auto it = find(array.begin(), array.end(), s);

	if (it != array.end())
		return true;
	else
		return false;
}

void searchBoyerMoore(){
	
	string sentences, pattern;
	cout << "Введите предложение." << endl;
	getline(cin, sentences);
	getline(cin, pattern);

	vector<char> uniq;//Словать уникальных значений
	int len = pattern.length();//длина предложения
	map<char, unsigned> shift;//Словарь смещения

	for (int i = len - 2; i >= 0; i--) {//Итерация с предпоследнего символа
		if (findArray(pattern[i], uniq))
			continue;

		shift[pattern[i]] = len - i - 1;
		uniq.push_back(pattern[i]);
	}

	if (findArray(pattern[len-1], uniq))//Формируем смещение для последнего символа
		shift[pattern[len - 1]] = len;

	shift['*'] = len;//Смещение для прочих символов

	int len_s = sentences.length();
	//Длина строки меньше подстроки, то можно неискать
	if (len_s < len)
		return;

	int i = len - 1, off, k;
	while (i < len_s) {
		k = 0;
		for (int j = len - 1; j >= 0; j--) {
			//Сравниваемые символы не равны
			if (sentences[i - k] != pattern[j]) {
				//Если сравниваемый символ является последним, то ищем шаг сдвига в словаре shift иначе
				//сдвигаем сравниваемый символ подстроки
				if (j == len - 1) {
					if (shift.count(sentences[i]) == 1)
						off = shift[sentences[i]];
					else
						off = shift['*'];
				}
				else
					off = shift[pattern[j]];

				i += off;
				break;
			}
			k++;

			if (j == 0) {
				cout << "Образ найден по индексу: " << i - k + 1 << endl;
				i++;
			}
		}
	}
}



int main(){
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	//createArray();
	searchBoyerMoore();

	return 0;
}