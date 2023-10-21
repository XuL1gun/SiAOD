#include "Huffman.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

struct CompareNodes {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->frequency > b->frequency;
    }
};

HuffmanNode* buildHuffmanTree(map<char, unsigned>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, CompareNodes> pq;

    // Создаем листовые узлы для каждого символа и добавляем их в очередь с приоритетом
    for (auto& freq : frequencies) {
        pq.push(new HuffmanNode(freq.first, freq.second));
    }

    while (pq.size() > 1) {
        // Извлекаем два узла с наименьшей частотой из очереди
        HuffmanNode* left = pq.top();
        pq.pop();
        HuffmanNode* right = pq.top();
        pq.pop();

        // Создаем новый узел суммирующий частоты двух извлеченных узлов
        HuffmanNode* newNode = new HuffmanNode('#', left->frequency + right->frequency);
        newNode->left = left;
        newNode->right = right;

        // Добавляем новый узел в очередь с приоритетом
        pq.push(newNode);
    }

    // Корневой узел дерева
    return pq.top();
}

// Функция для кодирования символов в двоичные строки
void encodeHuffmanTree(HuffmanNode* root, string code, map<char, string>& huffmanCodes) {
    if (root == nullptr) {
        return;
    }

    // Если узел является листом, то сохраняем код символа
    if (!root->left && !root->right) {
        huffmanCodes[root->data] = code;
    }

    // Рекурсивно обходим левое и правое поддерево
    encodeHuffmanTree(root->left, code + "0", huffmanCodes);
    encodeHuffmanTree(root->right, code + "1", huffmanCodes);
}

string line;

void encodeHuffman() {
    map<char, unsigned> frequencies;
	cout << "Введите фразу: ";
	getline(cin, line);

	//Заполняем количеством символах встретившихся в фразе
	for (char ch : line)
        frequencies[ch] ++;

    // Построение дерева Хаффмана
    HuffmanNode* root = buildHuffmanTree(frequencies);

    // Создание таблицы символов с их кодами Хаффмана
    map<char, string> huffmanCodes;
    encodeHuffmanTree(root, "", huffmanCodes);

    string compressedData = "";
    for (char c : line) {
        compressedData += huffmanCodes[c] + " ";
    }

    cout << compressedData;
}