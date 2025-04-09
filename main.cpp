#include "tokenizer.h"
#include <iostream>

using namespace std;

int main() {
    Tokenizer tokenizer;

    tokenizer.readFromFile("verdict.txt");

    cout << "\nTokens found in file:\n";
    tokenizer.printAllTokens();

    string word;
    cout << "\nEnter a word to get its token: ";
    cin >> word;
    int token = tokenizer.getTokenFromWord(word);
    cout << "Token for \"" << word << "\": " << token << "\n";

    int inputToken;
    cout << "\nEnter a token number to get the word: ";
    cin >> inputToken;
    cout << "Word for token " << inputToken << ": " << tokenizer.getWordFromToken(inputToken) << "\n";

    return 0;
}
