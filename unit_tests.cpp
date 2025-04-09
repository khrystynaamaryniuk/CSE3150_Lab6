#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "tokenizer.h"

TEST_CASE("Tokenizer assigns correct tokens to words") {
    Tokenizer tokenizer;
    tokenizer.readFromLine("algorithm data structure compiler operating system");

    CHECK(tokenizer.getTokenFromWord("algorithm") != -1);
    CHECK(tokenizer.getTokenFromWord("data") != -1);
    CHECK(tokenizer.getTokenFromWord("structure") != -1);
    CHECK(tokenizer.getTokenFromWord("compiler") != -1);
    CHECK(tokenizer.getTokenFromWord("operating") != -1);
    CHECK(tokenizer.getTokenFromWord("system") != -1);

    int token = tokenizer.getTokenFromWord("compiler");
    CHECK(tokenizer.getWordFromToken(token) == "compiler");
}

TEST_CASE("Tokenizer handles missing words") {
    Tokenizer tokenizer;
    tokenizer.readFromLine("algorithm data structure compiler");

    CHECK(tokenizer.getTokenFromWord("network") == -1);  // network is not in the map
    CHECK(tokenizer.getWordFromToken(1000) == "Invalid Token");
}

TEST_CASE("Tokenizer handles empty input") {
    Tokenizer tokenizer;
    tokenizer.readFromLine("");

    CHECK(tokenizer.getTokenFromWord("anything") == -1);
    CHECK(tokenizer.getWordFromToken(0) == "Invalid Token");
}

TEST_CASE("Tokenizer handles punctuation and symbols") {
    Tokenizer tokenizer;
    tokenizer.readFromLine("algorithm, data! structure; compiler: operating system?");

    CHECK(tokenizer.getTokenFromWord("algorithm") != -1);
    CHECK(tokenizer.getTokenFromWord("data") != -1);
    CHECK(tokenizer.getTokenFromWord("structure") != -1);
    CHECK(tokenizer.getTokenFromWord("compiler") != -1);
    CHECK(tokenizer.getTokenFromWord("operating") != -1);
    CHECK(tokenizer.getTokenFromWord("system") != -1);

    CHECK(tokenizer.getTokenFromWord("algorithm!") == -1);  // Should not count as "algorithm!"
    CHECK(tokenizer.getTokenFromWord("data.") == -1);  // Should not count as "data."
}

TEST_CASE("Tokenizer reads from file correctly") {
    Tokenizer tokenizer;
    tokenizer.readFromFile("verdict.txt");

    // Test some expected tokens from file.txt
    CHECK(tokenizer.getTokenFromWord("I") != -1);
    CHECK(tokenizer.getTokenFromWord("HAD") != -1);
    CHECK(tokenizer.getTokenFromWord("splash") != -1);
    CHECK(tokenizer.getTokenFromWord("too") != -1);
}

TEST_CASE("Tokenizer returns correct token for repeated words") {
    Tokenizer tokenizer;
    tokenizer.readFromLine("algorithm data structure algorithm compiler");

    CHECK(tokenizer.getTokenFromWord("algorithm") == 0);  // First occurrence
    CHECK(tokenizer.getTokenFromWord("data") == 1);
    CHECK(tokenizer.getTokenFromWord("structure") == 2);
    CHECK(tokenizer.getTokenFromWord("compiler") == 3);
}


TEST_CASE("Tokenizer handles edge case with large tokens") {
    Tokenizer tokenizer;
    string largeWord = string(1000, 'x');  // 1000 'x' characters
    tokenizer.readFromLine(largeWord);

    CHECK(tokenizer.getTokenFromWord(largeWord) != -1);
    CHECK(tokenizer.getWordFromToken(0) == largeWord);
}


TEST_CASE("Tokenizer handles multiple spaces between words") {
    Tokenizer tokenizer;
    tokenizer.readFromLine("algorithm    data   structure");

    CHECK(tokenizer.getTokenFromWord("algorithm") != -1);
    CHECK(tokenizer.getTokenFromWord("data") != -1);
    CHECK(tokenizer.getTokenFromWord("structure") != -1);
}



TEST_CASE("Tokenizer handles empty lines in file") {
    Tokenizer tokenizer;
    tokenizer.readFromFile("emptyfile.txt");  // Ensure there is an empty line in the file

    CHECK(tokenizer.getTokenFromWord("empty") == -1);  // Should be no tokens for an empty line
}

