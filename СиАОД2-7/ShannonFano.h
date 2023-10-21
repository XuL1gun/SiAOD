#include <string>
#include <vector>

#ifndef SHANNONFANO_H
#define SHANNONFANO_H

using namespace std;

struct Node {
	int symbol;
	double probability;
	string code;

	Node(int sym, double prob) : symbol(sym), probability(prob), code("") {}
};

bool compareNodes(const Node* node1, const Node* node2);
void shannonFano(vector<Node*>& nodes, int start, int end);
void encodeShenon();
void decodeShannonFano();

#endif

