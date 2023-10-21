#include <iostream>
#include <Windows.h>
#include <cstring>

using namespace std;

struct Node {
	string key;
	string name;
	Node* next;

	Node(string key, string name) :key(key), name(name), next(nullptr){}
};

struct HashTable {

	int size;
	int amount;
	Node** array = (struct Node**)malloc(sizeof(struct Node*) * size);//Выделили память вод массив
	bool flag;

	HashTable(int size, int amount) :size(size), amount(amount), flag(true), array((struct Node**)malloc(sizeof(struct Node*)* size)) {
		for (int i = 0; i < this->size; i++)
			this->array[i] = nullptr;
	}

	void createTable() {
		int n = 7, i = 0;
		string key;
		string name;

		while (i != n) {
			key = (char)(rand() % 26 + 65);
			name = (char)(rand() % 26 + 65);
			if (this->findNode(key) == nullptr) {
				this->insert(this->array, key, name);
				i++;
			}
		}
	}

	void rehashingArray() {
		HashTable* help = new HashTable((this->size*2), 0);

		Node* node;

		for (int i = 0; i < size; i++) {
			node = this->array[i];

			if (node == nullptr)
				continue;

			while (node->next != nullptr) {
				help->insert(help->array, node->key, node->name);

				node = node->next;
			}

			help->insert(help->array, node->key, node->name);
		}

		this->array = help->array;
		size = help->size;

		delete help;
	}

	void insert(Node** &array, string key, string name) {

		Node* newNode = new Node(key, name);

		if (findNode(newNode->key) != nullptr) {
			cout << "Значение с таким ключом уже существует" << endl;
			return;
		}


		int numberOfarray = hash<string>()(key) % this->size;

		if (this->array[numberOfarray] == nullptr)
			this->array[numberOfarray] = newNode;
		else {
			Node* node = this->array[numberOfarray];
			while (node->next != nullptr)
				node = node->next;

			node->next = newNode;
		}

		amount++;

		if ((double)this->amount / this->size > 0.75)
			this->rehashingArray();
	}

	void deleteNode(string key) {

		int numberOfarray = hash<string>()(key) % this->size;

		if (this->findNode(key) == nullptr) {
			cout << "Введенного вами ключа нет в таблице." << endl;
			return;
		}

		if (this->array[numberOfarray]->key == key){
			Node* deleteNode = this->array[numberOfarray];
			this->array[numberOfarray] = deleteNode->next;
			delete deleteNode;
		}
		else {
			Node* node = this->array[numberOfarray]->next;
			Node* helpNode = this->array[numberOfarray];
			Node* deleteNode;

			while (node->next != nullptr) {
				if (node->key == key) {
					helpNode->next = node->next;
					delete node;
				}
				helpNode = node;
				node = node->next;
			}

			if (node->key == key) {
				helpNode->next = nullptr;
				delete node;
			}

		}
		this->amount--;

	}

	Node* findNode(string key) {

		int numberOfarray = hash<string>()(key) % this->size;

		Node* findNode = this->array[numberOfarray];

		if (findNode == nullptr) {
			return nullptr;
		}

		while (findNode->next != nullptr) {
			if (findNode->key == key)
				return findNode;

			findNode = findNode->next;
		}

		if (findNode->key == key)
			return findNode;
		else {
			return nullptr;
		}
	}

	void printNode() {
		Node* node = nullptr;

		for (int i = 0; i < size; i++) {
			node = this->array[i];
			if (node != nullptr) {
				while (node->next != nullptr) {
					cout << "Ключевое значение " << node->key << " содержимое: " << node->name << "; ";

					node = node->next;
				}
				if (i != size - 1)
					cout << "Ключевое значение " << node->key << " содержимое: " << node->name << endl;
			}
		}
		if (node != nullptr)
			cout << "Ключевое значение " << node->key << " содержимое: " << node->name << endl;
	}
};

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	int n;

	HashTable* mp = new HashTable(3, 0);

	string key;
	string name;

	while (true) {
		cout << "Ведите комманду: \n1 - вставить узел \n2 - удалить узел \n3 - поиск узла по ключу \n4 - вывести хеш таблицу \n5 - Создать автоматически \n6 - выйти из цикла \n";
		cin >> n;
		switch (n){
		case 1:
			cout << "Введите направление и Университет ";
			cin >> key >> name;
			mp->insert(mp->array, key, name);
			break;
		case 2:
			if (mp->amount != 0) {
				cout << "Введите ключ по которому хотите удалить элемент ";
				cin >> key;
				mp->deleteNode(key);
			}
			else {
				cout << "Таблица пуста" << endl;
			}
			break;
		case 3:
			if (mp->amount != 0) {
				cout << "Введите ключ по которому хотите найти элемент ";
				cin >> key;
				Node* newNode = mp->findNode(key);
				if (newNode != nullptr)
					cout << newNode->name << endl;
				else
					cout << "Значения с таким ключом нет." << endl;
			}
			else {
				cout << "Таблица пуста" << endl;
			}
			break;
		case 4:
			if (mp->amount != 0)
				mp->printNode();
			else
				cout << "Таблица пуста" << endl;
			break;
		case 5:
			mp->createTable();
			break;
		case 6:
			return 0;
		default:
			break;
		}
		cout << "Хотите очистить консоль? (1 - Да/0 - Нет) ";
		cin >> n;
		if (n == 1)
			system("cls");
	}
	return 0;
}