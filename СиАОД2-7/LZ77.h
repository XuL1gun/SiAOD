#ifndef LZ77_H
#define LZ77_H
#include <string>


using namespace std;

struct Pair {
    int offset;
    int len;
    char symbol;
};

void lz77Encode(const string& phrase);
#endif
