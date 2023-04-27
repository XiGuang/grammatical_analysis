//
// Created by xiguang on 2023/4/14.
//

#include "Lexer.h"
#include <iostream>
#include <fstream>
#include "../Error/Error.h"

Token Lexer::nextToken() {
    bool valid = true;
    std::string error_string;
    Token token = nextToken(valid);
    while (!valid) {
        valid = true;
        error_string += token.value;
        token = nextToken(valid);
    }
    if (!error_string.empty())
        Error::getInstance().error("Invalid character: " + error_string);
    return token;
}

Token Lexer::nextToken(bool &valid) {
    if (position >= input.length()) {
        return {"EOF", ""};
    } else if (input[position] == ' ' || input[position] == '\n' || input[position] == '\t') {
        position++;
        return nextToken(valid);
    } else if (std::isdigit(input[position])) {
        std::string number;
        while (std::isdigit(input[position])) {
            number += input[position++];
        }
        return {"number", number};
    } else if (std::isalpha(input[position])) {
        std::string identifier;
        while (isalnum(input[position])) {
            identifier += std::tolower(input[position++]);
        }
        if (identifier == "if") {
            return {"ifsym", identifier};
        } else if (identifier == "then") {
            return {"thensym", identifier};
        } else if (identifier == "odd") {
            return {"oddsym", identifier};
        } else if (identifier == "begin") {
            return {"beginsym", identifier};
        } else if (identifier == "end") {
            return {"endsym", identifier};
        } else if (identifier == "call") {
            return {"callsym", identifier};
        } else if (identifier == "const") {
            return {"constsym", identifier};
        } else if (identifier == "do") {
            return {"dosym", identifier};
        } else if (identifier == "while") {
            return {"whilesym", identifier};
        } else if (identifier == "read") {
            return {"readsym", identifier};
        } else if (identifier == "write") {
            return {"writesym", identifier};
        } else if (identifier == "var") {
            return {"varsym", identifier};
        } else if (identifier == "procedure") {
            return {"proceduresym", identifier};
        } else if (identifier == "const") {
            return {"constsym", identifier};
        } else {
            return {"ident", identifier};
        }
    } else if (input[position] == '(') {
        position++;
        return {"lparen", "("};
    } else if (input[position] == ')') {
        position++;
        return {"rparen", ")"};
    } else if (input[position] == '+') {
        return {"plus", std::string(1, input[position++])};
    } else if (input[position] == '-') {
        return {"minus", std::string(1, input[position++])};
    } else if (input[position] == '*') {
        return {"times", std::string(1, input[position++])};
    } else if (input[position] == '/') {
        return {"slash", std::string(1, input[position++])};
    } else if (input[position] == ',') {
        return {"comma", std::string(1, input[position++])};
    } else if (input[position] == ';') {
        return {"semicolon", std::string(1, input[position++])};
    } else if (input[position] == '.') {
        return {"period", std::string(1, input[position++])};
    } else if (input[position] == '=') {
        return {"eql", std::string(1, input[position++])};
    } else if (input[position] == '<') {
        if (input[position + 1] == '=') {
            position += 2;
            return {"leq", "<="};
        } else {
            position++;
            return {"lss", "<"};
        }
    } else if (input[position] == '>') {
        if (input[position + 1] == '=') {
            position += 2;
            return {"geq", ">="};
        } else {
            position++;
            return {"gtr", ">"};
        }
    } else if (input[position] == ':' && input[position + 1] == '=') {
        position += 2;
        return {"becomes", ":="};
    } else if (input[position] == '#') {
        return {"neq", std::string(1, input[position++])};
    }
    valid = false;
    return {"", std::string(1, input[position++])};
}

bool Lexer::eof() const {
    return position >= input.size();
}

void Lexer::saveTokenStream(const std::string &path) {
    std::ofstream file(path, std::fstream::out);
    int now_position(position);
    position = 0;
    while (!eof()) {
        file << nextToken() << std::endl;
    }
    position = now_position;
    file.close();
}


