#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
#include <map>
#include <vector>

using namespace std;

class Tokenizer {
private:
    map<string, int> wordToToken;
    vector<string> tokenToWord;
    int currentToken;

    string cleanUpWord(const string& word); // remove punctuation

public:
    Tokenizer();

    void readFromFile(const string& fileName);
    void printAllTokens() const;

    int getTokenFromWord(const string& word) const;
    string getWordFromToken(int token) const;

    void readFromLine(const string& line); 
};

#endif


