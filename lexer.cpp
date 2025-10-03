#include <iostream>
#include "patterns.h"
#include <optional>
#include <fstream>

using namespace std;

struct Token {
    string type;
    string_view text;
};

string readFile(const string &fileName) {
    ifstream file(fileName);
    if (file.is_open()) {
        string content((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();
        return content;
    } else {
        cerr << "Unable to open file: " << fileName << endl;
        return "";
    }
}

optional<Token> lexer(const string &input, size_t &currentPosition) {
    const auto rules = compiledRegexes();

    const auto n = input.size();
    if (currentPosition >= n) return nullopt;

    size_t bestSize = 0;
    string bestType;
    match_results<string::const_iterator> m;

    auto it_begin = input.cbegin() + static_cast<ptrdiff_t>(currentPosition);
    auto it_end   = input.cend();

    for (const auto &reg : rules) {
        const string &type = reg.first;
        const regex &regularExpression = reg.second;

        if (regex_search(it_begin, it_end, m, regularExpression, regex_constants::match_continuous)) {
            size_t len = static_cast<size_t>(m.length(0));
            if (len == 0) continue; 
            if (len > bestSize) {
                bestSize = len;
                bestType = type;
            }
        }
    }

    if (bestSize == 0) {
        Token t{"UNKNOWN", string_view(input.data() + currentPosition, 1)};
        ++currentPosition;
        return t;
    }

    Token tok{bestType, string_view(input.data() + currentPosition, bestSize)};
    currentPosition += bestSize;
    return tok;
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        return 1;
    }
     string src = readFile(argv[2]);

    if (src.empty()) {
        return 1;
    }

    size_t currentPosition = 0;
    while (true) {
        auto tk = lexer(src, currentPosition);
        if (!tk) break;
        if (tk->type == "SPACE" || tk->type == "NEWLINE") continue;
        cout << "<" << tk->text << ", " << tk->type << ">\n";
    }
    return 0;
}