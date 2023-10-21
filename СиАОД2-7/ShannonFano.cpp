#include "ShannonFano.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <string>

using namespace std;

bool compareNodes(const Node* node1, const Node* node2) {
	return node1->probability > node2->probability;
}

void shannonFano(vector<Node*>& nodes, int start, int end) {
	if (start == end)
		return;

	int splitIndex = 0;
	double sumLeft = 0, sumRight = 0;
	//Инициализируем максимальным значением типа double
	double minDifference = 10000;//numeric_limits<double>::max();

	//Находим минимальную разницу между двумя группами
	for (int i = start; i < end; ++i) {
		sumLeft = 0.0;
		sumRight = 0.0;

		for (int j = start; j <= i; ++j)
			sumLeft += nodes[j]->probability;

		for (int j = i + 1; j <= end; ++j)
			sumRight += nodes[j]->probability;

		double difference = abs(sumLeft - sumRight);
		if (difference < minDifference) {
			minDifference = difference;
			splitIndex = i;
		}
	}

	for (int i = start; i <= splitIndex; ++i)
		nodes[i]->code += "0";

	for (int i = splitIndex + 1; i <= end; ++i)
		nodes[i]->code += "1";
	//Делаим на две группы
	shannonFano(nodes, start, splitIndex);
	shannonFano(nodes, splitIndex + 1, end);
}

vector<Node*> nodes;
string str;
string codePhrase = "";

void encodeShenon() {
	cout << "Введите фразу: ";
	getline(cin, str);

	vector<int> array(256, 0);

	//Заполняем количеством символах встретившихся в фразе
	for (char ch : str)
		if ((int)ch < 0)
			array[(int)ch + 192] ++;
		else
			array[ch] ++;

	for (int i = 0; i < 256; i++) {
		if (array[i] > 0) {
			int a = i;
			double b = static_cast<double>(array[i]) / str.size();
			nodes.push_back(new Node(a, b));
		}
	}

	//Сортируем в порядке убывания их частоты встречи
	sort(nodes.begin(), nodes.end(), compareNodes);

	//Кодируем используя второй этап кодировки
	shannonFano(nodes, 0, nodes.size() - 1);

	
	for (char ch : str) {
		for (Node* node : nodes) {
			int n;
			if (ch < 0)
				n = ch + 192;
			else
				n = ch;
			if (n == node->symbol) {
				codePhrase += node->code;
			}
		}
	}

	cout << "Кодовая фраза: " << codePhrase << endl;
}

void decodeShannonFano() {
	string decoded;
	string currentCode;

	for (char c : codePhrase) {
		currentCode += c;

		for (Node* node : nodes) {
			if (currentCode == node->code) {
				if (node->symbol > 127)
					decoded += (char)(node->symbol - 192);
				else
					decoded += (char)node->symbol;
				currentCode = "";
				break;
			}
		}
	}

	std::cout << "Decoded message: " << decoded << std::endl;
}