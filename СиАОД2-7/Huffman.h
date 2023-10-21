#ifndef HUFFMAN_H
#define HUFFMAN_H
#include <string>
#include <map>

using namespace std;

struct HuffmanNode {
    char data;
    unsigned frequency;
    HuffmanNode* left, * right;

    HuffmanNode(char data, unsigned frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

HuffmanNode* buildHuffmanTree(map<char, unsigned>& frequencies);
void encodeHuffmanTree(HuffmanNode* root, string code, map<char, string>& huffmanCodes);
void encodeHuffman();
#endif
