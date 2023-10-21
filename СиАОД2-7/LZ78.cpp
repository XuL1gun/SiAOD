#include "LZ78.h"
#include <vector>
#include <iostream>

bool find(string str, vector<Code*> nodes, int &n) {
	for (int i = 0; i < nodes.size(); i++)
		if (str == nodes[i]->symbol) {
			n = nodes[i]->index;
			return true;
		}

	return false;
}

void lz78Encode(const string& phrase) {

	string str = "";
	vector <Code*> dictionary;
	vector <Code*> nodes;
	int n = 0;

	for (int i = 0; i < phrase.size(); i++) {
		str += phrase[i];
		if (!find(str, dictionary, n)) {
			dictionary.push_back(new Code(dictionary.size() + 1, str));
			nodes.push_back(new Code(n, phrase[i]));
			n = 0;
			str = "";
		}
	}

	for (Code* node: nodes) {
		cout << "<" << node->index << ", " << node->sym << "> ";
	}
}