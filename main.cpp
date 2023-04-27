#include <iostream>
#include <string>
#include "Lexer/Lexer.h"
#include "Parser/Parser.h"
#include "Error/Error.h"

using namespace std;

int main() {

//    Parser parser(R"(F:\programme\codes\c++\grammatical_analysis\input\token\token_1.txt)");

//    string input = "num1*5)+9) (num1+4 num2)";
//    Lexer lexer(input);
//    lexer.saveTokenStream(R"(F:\programme\codes\c++\grammatical_analysis\input\token\token_15.txt)");
//    Parser parser(R"(F:\programme\codes\c++\grammatical_analysis\input\token\token_15.txt)");

    string input = "if a = 1 + 2 * 3 then b     := 1 ";
    Lexer lexer(input);
    Parser parser(lexer);

    string result;
    parser.start(result);
    cout<<"result: "<<result<<endl;
    if(!Error::getInstance().hasErrorOccurred())
        cout<<"no error occurred"<<endl;
    return 0;
}
