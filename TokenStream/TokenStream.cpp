//
// Created by xiguang on 2023/4/14.
//

#include "TokenStream.h"

TokenStream::TokenStream(const std::string &fileName) : lexer("") {
    file.open(fileName, std::ios::in);
}

TokenStream &TokenStream::operator>>(Token &token) {
    if (file.is_open()) {
        std::string temp;   // 临时变量，用于读取无用的字符
        std::string type;
        std::string value;
        file >> temp >> type >> temp >> value >> temp;
        if (type.empty())
            token = Token("EOF", "");
        else
            token = Token(type, value);
    } else {
        token = lexer.nextToken();
    }
    return *this;
}

TokenStream::~TokenStream() {
    if (file.is_open())
        file.close();
}

bool TokenStream::eof() const {
    if (file.is_open())
        return file.eof();
    return lexer.eof();
}
