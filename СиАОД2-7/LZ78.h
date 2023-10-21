#ifndef LZ78_H
#define LZ78_H
#include <string>
#include <vector>

using namespace std;

struct Code {
	int index;
	string symbol;
	char sym;

	Code(int index, string symbol) : index(index), symbol(symbol), sym(NULL) {}
	Code(int index, char symbol) : index(index), symbol(""), sym(symbol) {}
};

bool find(string str, vector<Code*> nodes, int &n);
void lz78Encode(const string& phrase);
#endif
