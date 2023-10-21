#include <iostream>
#include <Windows.h>
#include <bitset>
#include <vector>
#include <fstream>
#include <string> 

using namespace std;

inline void first_a() {
	unsigned char x = 255; // 8-разрядное двоичное число 11111111
	unsigned char maska = 1; //1=00000001 — 8-разрядная маска
	x = x & (~(maska << 4)); //результат x = 239*/

	cout << (int)x;
}

inline void first_b() {
	unsigned char x = 57; // 8-разрядное двоичное число 00111001
	unsigned char maska = 1; //1=00000001 — 8-разрядная маска
	x = x | (maska << 6);

	cout << (int)x;
}

void first_v() {
	unsigned int x = 25;
	const int n = sizeof(int) * 8; //=32 - количество разрядов в числе типа int
	unsigned maska = (1 << (n - 1)); //1 в старшем бите 32-разрядной сетки
	cout << "Начальный вид маски: " << bitset<n>(maska) << endl;
	cout << "Результат: ";
	for (int i = 1; i <= n; i++) { //32 раза - по количеству разрядов

		cout << (((x & maska)) >> (n - i));
		maska = maska >> 1; // смещение 1 в маске на разряд вправо
	}

	cout << endl;
	system("pause");
}

void second_a() {
	cout << "Введите размер динамического массива не более 8 и не менее 1" << endl;

	int n, num;

	unsigned char maska, bit_mas = 0;

	cin >> n;

	int* mas = new int[n]; //Создаем массив mas размерностью n

	for (int i = 0; i < n; i++) { // заполняем массив с клавиатуры числами от 0 до 7
		cout << "Введите элемент массива от 0 до 7: ";
		cin >> num;
		mas[i] = num;
	}

	for (int i = 0; i < n; i++) {//Заполняем с помощью маски битовый массив
		maska = 1;
		maska = (maska << (mas[i]));
		bit_mas = bit_mas | maska;
	}

	for (int i = 0; i < 8; i++) {//Узнаем на каком месте в битовом массиве расположена 1 и выводим на экран пользователя
		if ((bit_mas & 1) == 1)
			cout << i << " ";
		bit_mas >>= 1;
	}

	cout << endl;
}

void second_b() {
	int n, num;

	unsigned long long int maska, bit_mas = 0;

	cout << "Введите размер массива от 1 до 64: ";

	cin >> n;

	int* mas = new int[n]; //Создаем массив mas размерностью n

	for (int i = 0; i < n; i++) {// заполняем массив с клавиатуры числами от 0 до 63
		cout << "Введите элемент массива от 0 до 64: ";
		cin >> num;
		mas[i] = num;
	}

	for (int i = 0; i < n; i++) {//Заполняем с помощью маски битовый массив
		maska = 1;
		maska = (maska << (mas[i]));
		bit_mas = bit_mas | maska;
	}

	for (int i = 0; i < sizeof(bit_mas) * 8; i++) {//Узнаем на каком месте в битовом массиве расположена 1 и выводим на экран пользователя
		if ((bit_mas & 1) == 1)
			cout << i << " ";
		bit_mas >>= 1;
	}

	cout << endl;
}

void second_v() {
	int n, ch;

	unsigned char maska = 1;

	cout << "Введите размер массива от 0 до 64: ";

	cin >> n;

	vector <unsigned char> mas(8);

	for (int i = 0; i < n; i++) {//Заполняем битовый массив числами введенными с клавиатуры
		cout << "Введите элемент массива от 0 до 64: ";
		cin >> ch;
		mas[ch / 8] = mas[ch / 8] | (maska << ch % 8);
	}

	for (int i = 0; i < 8; i++) {//Выводим на экран пользователя отсортированный массив чисел
		for (int j = 0; j < 8; j++) {
			if ((mas[i] & 1) == 1)
				cout << 8 * i + j << " ";
			mas[i] >>= 1;
		}
	}
}

void third() {

	const int n = 10000000/8;

	int start = clock();

	unsigned char maska = 1;

	vector <unsigned char> bit_mas(n);//Создаем линейный массив размерность n из элементов типа unsigned char

	string path = "File.txt";

	ifstream fin;
	fin.open(path);

	if (!fin.is_open())
		cout << "Оибка открытия файла" << endl;
	else {

		int ch;

		while (!fin.eof()) {//Заполняем битовый массив числами считанными из файла
			fin >> ch;
			bit_mas[ch / 8] = bit_mas[ch / 8] | (maska << ch % 8);
		}
	}

	fin.close();

	int stop = clock();

	ofstream fout;
	fout.open(path);


	if (!fout.is_open())
		cout << "Оибка открытия файла" << endl;
	else {

		for (int i = 0; i < (n); i++) {//Записываем отсортированную последовательность в файл
			for (int j = 0; j < 8; j++) {
				if ((bit_mas[i] & 1) == 1)
					fout << 8 * i + j << endl;
				bit_mas[i] >>= 1;
			}
		}
	}
	fout.close();


	int resTime = stop - start;//Высчитываем время, которое заняло выполнение программы

	bit_mas.shrink_to_fit();

	cout << bit_mas.capacity() << " Байт" << endl;

	cout << bit_mas.capacity() / 1024 << " КБ" << endl;

	cout << bit_mas.capacity() / (1024 * 1024) << " МБ" << endl;

	cout << "Time: " << resTime << " ms \n";
}

void create_file() {

	const long n = 1000000;
	const long n_max = 9999999;
	const int len = n_max - n + 1;
	long* array = new long [len];

	for (long i = 0; i < len; i++) {
		array[i] = n + i;
	}
	
	srand(time(NULL));

	for (long i = 0; i < len; i++)
		swap(array[i], array[rand() % len]);

	ofstream fout;
	fout.open("Test.txt");


	if (!fout.is_open())
		cout << "Оибка открытия файла" << endl;
	else {
		for (int i = 0; i < len; i++)
			fout << array[i] << endl;
	}
	fout.close();
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	cout << "Выберите номер задания 1, 2 или 3: ";
	
	char letter;

	int n;
	cin >> n;

	switch (n) {
		case 1:
			cout << "Введите букву пункта задания а, б или в: ";
			cin >> letter;
			if (letter == 'а')
				first_a();
			else if (letter == 'б')
				first_b();
			else
				first_v();
			break;
		case 2:
			cout << "Введите букву пункта задания а, б или в: ";
			cin >> letter;
			if (letter == 'а')
				second_a();
			else if (letter == 'б')
				second_b();
			else
				second_v();
			break;
		case 3:
			//create_file();
			third();
			break;
	default:
		break;
	}

	return 0;
} 