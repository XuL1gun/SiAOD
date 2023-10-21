#define _CRT_SECURE_NO_DEPRECATE
#include <iostream>
#include <random>
#include <fstream>
#include <Windows.h>

using namespace std;

const int n = 10000;

int start;
int stop;

struct tab {
	int key;
	int shift;
};

struct Read_Sub
{
	int number = 0;
	char surname = ' ';
	char name = ' ';
	char fathername = ' ';
	char address = ' ';
};

void select_sort(tab* &x, int n)
{
	int min;
	tab tmp;

	for (int i = 0; i < n - 1; i++) // Проходим по всему массиву из n элементов
	{
		min = i;
		for (int j = i + 1; j < n; j++)
		{
			if (x[min].key > x[j].key) // вторым циклом и условием находим индекс минимального элемента
			{
				min = j;
			}
		}
		tmp = x[i]; // меняем текущий элемент с минимальным местами
		x[i] = x[min];
		x[min] = tmp;
	}
}

void create_tex() {

	bool flag = true;

	Read_Sub* arr = new Read_Sub[n];

	//Создаем массив структуры, которая имеет уникальный ключ
	for (int i = 0; i < n; i++) {
		int ch = rand() % 10000 + 10000;
		for (int j = 0; j < n; j++) {
			if (arr[i].number == ch) {
				flag = false;
				break;
			}
		}

		if (flag) {
			arr[i].number = ch;
			arr[i].surname = (char)(rand() % 26 + 65);
			arr[i].name = (char)(rand() % 26 + 65);
			arr[i].fathername = (char)(rand() % 26 + 65);
			arr[i].address = (char)(rand() % 26 + 97);
		}
	}

	ofstream fout;
	string path = ("Text.txt");

	fout.open(path);

	//Записываем массив в файл с расширением .txt
	if (!fout.is_open())
		cout << "Ошибка открытия файла.";
	else {
		for (int i = 0;i < n; i++) {
			fout << endl << arr[i].number << " " << arr[i].surname << " " <<
				arr[i].name << " " << arr[i].fathername << " " << arr[i].address;
			//cout << arr[i].number << " " << arr[i].surname << " " <<
				//arr[i].name << " " << arr[i].fathername << " " << arr[i].address << endl;
		}
	}

	fout.close();
}

void create_bin() {

	Read_Sub* arr = new Read_Sub[n];

	string path = "Text.txt";

	ifstream fin;
	fin.open(path);

	//Считываем данные с файла в массив
	if (!fin.is_open())
		cout << "Ошибка отрытия файла.";
	else {
		for (int i = 0; i < n; i++) {
			fin >> arr[i].number >> arr[i].surname >>
				arr[i].name >> arr[i].fathername >> arr[i].address;
		}
	}

	fin.close();

	ofstream fout("Text.bin", ios::binary);


	//Выписываем в созданный бинарный файл
	if (!fout.is_open())
		cout << "Ошибка открытия файла.";
	else {
		for (int i = 0; i < n; i++) {
			fout.write((char*)&arr[i].number, sizeof(int));
			fout.write((char*)&arr[i].surname, sizeof(char));
			fout.write((char*)&arr[i].name, sizeof(char));
			fout.write((char*)&arr[i].fathername, sizeof(char));
			fout.write((char*)&arr[i].address, sizeof(char));
		}
	}
	fout.close();
}

void find_Text(int number) {
	Read_Sub* arr = new Read_Sub[n];

	FILE* fin = fopen("Text.bin", "rb");

	if (fin == NULL) {
		cout << "Ошибка открытия файла";
		exit(1);
	}

	//Линейным поиском ищем нужный ключ
	for (int i = 0; i < n; i++) {
		fread(&arr[i], sizeof(struct Read_Sub), 1, fin);
	}

	fclose(fin);

	for (int i = 0; i < n; i++) {
		if (arr[i].number == number) {
			cout << arr[i].number << " " << arr[i].surname << " " <<
				arr[i].name << " " << arr[i].fathername << " " << arr[i].address << endl;
			break;
		}
	}

}

int find_improve(int number) {

	Read_Sub* arr = new Read_Sub[n];
	tab* exel = new tab[n];

	FILE* fin = fopen("Text.bin", "rb");

	if (fin == NULL) {
		cout << "Ошибка открытия файла";
		exit(1);
	}

	//Создаем таблицу в которой хранится ключ и сдвиг
	for (int i = 0; i < n; i++) {
		fread(&arr[i], sizeof(struct Read_Sub), 1, fin);

		exel[i].key = arr[i].number;
		exel[i].shift = i;
	}

	fclose(fin);

	select_sort(exel, n);

	start = clock();
	int midd = 0, left = 0, right = (n-1);
	while (1)
	{
		midd = (left + right) / 2;

		if (number < exel[midd].key)       // если искомое меньше значения в ячейке
			right = midd - 1;      // смещаем правую границу поиска
		else if (number > exel[midd].key)  // если искомое больше значения в ячейке
			left = midd + 1;    // смещаем левую границу поиска
		else                       // иначе (значения равны)
			return exel[midd].shift;           // функция возвращает индекс ячейки

		if (left > right)          // если границы сомкнулись 
			return -1;
	}

	return 0;
}

void get_line(int n) {

	Read_Sub arr;

	//Выписываем нужную строку из текстового файла
	FILE* fin = fopen("Text.bin", "rb");

	if (fin == NULL) {
		cout << "Ошибка открытия файла";
		exit(1);
	}

	fseek(fin, sizeof(Read_Sub) * n, SEEK_SET);

	fread(&arr, sizeof(struct Read_Sub), 1, fin);

	fclose(fin);

	cout << arr.number << " " << arr.surname << " " <<
		arr.name << " " << arr.fathername << " " << arr.address << endl;
	stop = clock();
}

int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	create_tex();
	create_bin();

	cout << "Введите номер читательского билета: ";
	int n;
	cin >> n;

	cout << "Введите тип поиска в файле. (1 - линейный/2 - усовершенствованный) ";
	int number, shift;
	cin >> number;

	switch (number){
	case 1:
		find_Text(n);
		break;
	case 2:
		shift = find_improve(n);
		get_line(shift);
		break;
	default:
		break;
	}
	int resTime = stop - start;//Высчитываем время, которое заняло выполнение программы 15596

	cout << "Time: " << resTime << " ms \n";

	return 0;
}