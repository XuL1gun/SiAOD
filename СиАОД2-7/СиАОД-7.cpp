#include "ShannonFano.h"
#include "LZ77.h"
#include "LZ78.h"
#include "Huffman.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <Windows.h>
#include <string>

using namespace std;

int main() {


	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	encodeHuffman();
	//encodeShenon();
	//decodeShannonFano();
	//lz78Encode("webwerbweberweberweb");
	return 0;
}