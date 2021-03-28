#include <iostream>
#include <string>
#include "include/lexer.h"


int main(){
    std::string s;
    lexer* lex = initLexer("");
    while (true){
        std::cin >> s;
        updateLexer(lex, s);
        carryToToken(lex);
    }
    return 0;
}