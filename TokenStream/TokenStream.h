//
// Created by xiguang on 2023/4/14.
//

#ifndef GRAMMATICAL_ANALYSIS_TOKENSTREAM_H
#define GRAMMATICAL_ANALYSIS_TOKENSTREAM_H

#include "..\Token.h"
#include <fstream>
#include "../Lexer/Lexer.h"

class TokenStream {
private:
    std::ifstream file;
    Lexer lexer;
public:
    explicit TokenStream(const std::string& fileName);

    explicit TokenStream(Lexer& lexer): lexer(lexer){}

    ~TokenStream();

    TokenStream& operator >> (Token& token);

    bool eof() const;

};


#endif //GRAMMATICAL_ANALYSIS_TOKENSTREAM_H
