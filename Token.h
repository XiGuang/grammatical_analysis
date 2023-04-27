//
// Created by xiguang on 2023/4/14.
//

#ifndef GRAMMATICAL_ANALYSIS_TOKEN_H
#define GRAMMATICAL_ANALYSIS_TOKEN_H

#include <string>
#include <iostream>

class Token {
public:
    std::string type;
    std::string value;

    Token(std::string type, std::string value) {
        this->type = std::move(type);
        this->value = std::move(value);
    }

    friend std::ostream& operator<<(std::ostream& out,const Token& token){
        out<<"( "<<token.type<<" , "<<token.value<<" )";
    }
};

#endif //GRAMMATICAL_ANALYSIS_TOKEN_H
