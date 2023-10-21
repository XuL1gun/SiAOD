#include "LZ77.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

void lz77Encode(const string& phrase) {
    vector<Pair> encoded;

    int phraseLength = phrase.length();
    int currentIndex = 0;

    while (currentIndex < phraseLength) {
        Pair currentPair;
        currentPair.offset = 0;
        currentPair.len = 0;
        currentPair.symbol = '-';

        // Поиск наибольшего совпадения с предыдущими символами
        for (int i = currentIndex - 1; i >= 0; i--) {
            int j = 0;
            while (j < phraseLength - currentIndex && phrase[i + j] == phrase[currentIndex + j]) {
                j++;
            }

            if (j > currentPair.len) {
                currentPair.offset = currentIndex - i - 1;
                currentPair.len = j;
                currentPair.symbol = phrase[currentIndex + j];
            }
        }

        encoded.push_back(currentPair);
        currentIndex += currentPair.len + 1;
    }

    for (const Pair& pair : encoded) {
        cout << "<" << pair.offset << ", " << pair.len << ", " << (char) pair.symbol << "> ";
    }
    cout << endl;
    
}