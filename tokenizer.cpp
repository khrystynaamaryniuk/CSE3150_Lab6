#include "tokenizer.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <regex>

using namespace std;

Tokenizer::Tokenizer() {
    currentToken = 0;
}

// Remove punctuation and symbols from the word
string Tokenizer::cleanUpWord(const string& word) {
    regex onlyLettersOrDigits("[a-zA-Z0-9]+");
    smatch match;
    if (regex_search(word, match, onlyLettersOrDigits)) {
        return match.str(0);
    }
    return "";
}

void Tokenizer::readFromFile(const string& fileName) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Could not open the file.\n";
        return;
    }

    string line;
    while (getline(file, line)) {
        readFromLine(line);
    }

    file.close();
}

void Tokenizer::readFromLine(const string& line) {
    istringstream input(line);
    string word;

    while (input >> word) {
        string cleanWord = cleanUpWord(word);

        if (!cleanWord.empty() && wordToToken.find(cleanWord) == wordToToken.end()) {
            wordToToken[cleanWord] = currentToken;
            tokenToWord.push_back(cleanWord);
            currentToken++;
        }
    }
}

void Tokenizer::printAllTokens() const {
    for (const auto& pair : wordToToken) {
        cout << pair.first << " => " << pair.second << "\n";
    }
}

int Tokenizer::getTokenFromWord(const string& word) const {
    auto it = wordToToken.find(word);
    if (it != wordToToken.end()) {
        return it->second;
    }
    return -1; 
}

string Tokenizer::getWordFromToken(int token) const {
    if (token >= 0 && token < tokenToWord.size()) {
        return tokenToWord[token];
    }
    return "Invalid Token";
}
