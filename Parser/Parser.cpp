//
// Created by xiguang on 2023/4/14.
//

#include "Parser.h"
#include "../Error/Error.h"


void Parser::eat() {
    tokenStream >> currentToken;
}

bool Parser::start(std::string &result) {
    bool valid = true;
    valid &= statement(result);
    if(currentToken.type =="rparen"){
        result += currentToken.value + " ";
        Error::getInstance().error("Need lparen before :" + result);
        valid = false;
    }else if (currentToken.type != "EOF") {
        Error::getInstance().error("Redundancy after :" + result);
        valid = false;
    }
    return valid;
}

bool Parser::factor(std::string &result) {
    bool valid = true;
    if (currentToken.type == "ident" || (currentToken.type == "number")) {
        result += currentToken.value + " ";
        eat();
    } else if (currentToken.type == "lparen") {
        result += currentToken.value + " ";
        eat();
        valid &= expression(result);
        if (currentToken.type == "rparen") {
            result += currentToken.value + " ";
            eat();
        } else {
            Error::getInstance().error("Need rparen after :" + result);
            valid = false;
        }
    } else {
        Error::getInstance().error("Need factor after :" + result);
        valid = false;
    }
    return valid;
}

bool Parser::term(std::string &result) {
    bool valid = true;
    valid &= factor(result);

    while (currentToken.type == "times" || currentToken.type == "slash") {
        result += currentToken.value + " ";
        eat();
        valid &= factor(result);
    }
    return valid;
}

bool Parser::expression(std::string &result) {
    bool valid = true;
    if (currentToken.type == "plus" || currentToken.type == "minus") {
        result += currentToken.value + " ";
        eat();
    }

    valid &= term(result);

    while (currentToken.type == "plus" || currentToken.type == "minus") {
        result += currentToken.value + " ";
        eat();
        valid &= term(result);
    }
    return valid;
}


bool Parser::conditionalExpression(std::string &result) {
    bool valid = true;
    if (currentToken.type == "oddsym") {
        result += currentToken.value + " ";
        eat();
        valid &= expression(result);
        return valid;
    }

    valid &= expression(result);
    if (currentToken.type == "eql" || currentToken.type == "neq" || currentToken.type == "lss" ||
        currentToken.type == "leq" ||
        currentToken.type == "gtr" || currentToken.type == "geq") {
        result += currentToken.value + " ";
        eat();
        valid &= expression(result);
    } else {
        Error::getInstance().error("Need op after :" + result);
        valid = false;
    }
    return valid;
}

bool Parser::conditionalStatement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "ifsym") {
        result += currentToken.value + " ";
        eat();
        valid &= conditionalExpression(result);
    } else {
        Error::getInstance().error("Need if after :" + result);
        return false;
    }
    if (currentToken.type == "thensym") {
        result += currentToken.value + " ";
        eat();
        valid &= statement(result);
    } else {
        Error::getInstance().error("Need then after :" + result);
        return false;
    }
    return valid;
}

bool Parser::statement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "ifsym") {
        valid &= conditionalStatement(result);
    } else if (currentToken.type == "whilesym") {
        valid &= loopStatement(result);
    } else if (currentToken.type == "callsym") {
        valid &= callStatement(result);
    } else if (currentToken.type == "beginsym") {
        valid &= compoundStatement(result);
    } else if (currentToken.type == "readsym") {
        valid &= readStatement(result);
    } else if (currentToken.type == "writesym") {
        valid &= writeStatement(result);
    } else if (currentToken.type == "ident") {
        valid &= assignmentStatement(result);
    }

    return valid;
}

bool Parser::assignmentStatement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "ident") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need ident after :" + result);
        return false;
    }
    if (currentToken.type == "becomes") {
        result += currentToken.value + " ";
        eat();
        valid &= expression(result);
    } else {
        Error::getInstance().error("Need becomes after :" + result);
        valid = false;
    }
    return valid;
}

bool Parser::loopStatement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "whilesym") {
        result += currentToken.value + " ";
        eat();
        valid &= conditionalExpression(result);
    } else {
        Error::getInstance().error("Need while after :" + result);
        return false;
    }
    if (currentToken.type == "dosym") {
        result += currentToken.value + " ";
        eat();
        valid &= statement(result);
    } else {
        Error::getInstance().error("Need do after :" + result);
        valid = false;
    }
    return valid;
}

bool Parser::callStatement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "callsym") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need call after :" + result);
        return false;
    }
    if (currentToken.type == "ident") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need ident after :" + result);
        valid = false;
    }
    return valid;
}

bool Parser::compoundStatement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "beginsym") {
        result += currentToken.value + " ";
        eat();
        valid &= statement(result);
    } else {
        Error::getInstance().error("Need begin after :" + result);
        return false;
    }
    while (currentToken.type == "semicolon") {
        result += currentToken.value + " ";
        eat();
        valid &= statement(result);
    }
    if (currentToken.type == "endsym") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need end after :" + result);
        valid = false;
    }
    return valid;
}

bool Parser::readStatement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "readsym") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need read after :" + result);
        return false;
    }
    if (currentToken.type == "lparen") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need lparen after :" + result);
        return false;
    }
    if (currentToken.type == "ident") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need ident after :" + result);
        return false;
    }
    while (currentToken.type == "comma") {
        result += currentToken.value + " ";
        eat();
        if (currentToken.type == "ident") {
            result += currentToken.value + " ";
            eat();
        } else {
            Error::getInstance().error("Need ident after :" + result);
            return false;
        }
    }
    if (currentToken.type == "rparen") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need rparen after :" + result);
        return false;
    }
    return valid;
}

bool Parser::writeStatement(std::string &result) {
    bool valid = true;
    if (currentToken.type == "writesym") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need write after :" + result);
        return false;
    }
    if (currentToken.type == "lparen") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need lparen after :" + result);
        return false;
    }
    valid &= expression(result);
    while (currentToken.type == "comma") {
        result += currentToken.value + " ";
        eat();
        valid &= expression(result);
    }
    if (currentToken.type == "rparen") {
        result += currentToken.value + " ";
        eat();
    } else {
        Error::getInstance().error("Need rparen after :" + result);
        return false;
    }
    return valid;
}



