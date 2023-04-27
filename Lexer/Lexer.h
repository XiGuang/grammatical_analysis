//
// Created by xiguang on 2023/4/14.
//

#ifndef GRAMMATICAL_ANALYSIS_LEXER_H
#define GRAMMATICAL_ANALYSIS_LEXER_H

#include <string>
#include <utility>
#include "../Token.h"

class Lexer {
private:
    std::string input;
    int position;

    Token nextToken(bool& valid);
public:
    explicit Lexer(std::string input):input(std::move(input)),position(0){}

    void saveTokenStream(const std::string& path);

    [[nodiscard]] bool eof() const;

    Token nextToken();

};


#endif //GRAMMATICAL_ANALYSIS_LEXER_H
