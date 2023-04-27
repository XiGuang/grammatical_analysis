//
// Created by xiguang on 2023/4/14.
//

#ifndef GRAMMATICAL_ANALYSIS_PARSER_H
#define GRAMMATICAL_ANALYSIS_PARSER_H

#include "../TokenStream/TokenStream.h"

class Parser {
public:
    explicit Parser(const std::string& input_file) : tokenStream(TokenStream(input_file)), currentToken(Token("", "")) {
        tokenStream>>currentToken;
    }

    explicit Parser(Lexer& lexer): tokenStream(lexer), currentToken(Token("", "")) {
        tokenStream>>currentToken;
    }

    bool start(std::string &result);

private:
    TokenStream tokenStream;
    Token currentToken;

    void eat();

    bool factor(std::string &result);

    bool term(std::string &result);

    bool expression(std::string &result);

    bool conditionalExpression(std::string &result);

    bool conditionalStatement(std::string &result);

    bool statement(std::string &result);

    bool assignmentStatement(std::string &result);

    bool loopStatement(std::string &result);

    bool callStatement(std::string &result);

    bool compoundStatement(std::string &result);

    bool readStatement(std::string &result);

    bool writeStatement(std::string &result);

};


#endif //GRAMMATICAL_ANALYSIS_PARSER_H
