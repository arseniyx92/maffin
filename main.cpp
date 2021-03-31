#include <iostream>
#include <fstream>
#include <string>
#include "include/lexer.h"
#include "include/imports.h"

int main(){
//    std::ifstream cin("example/eg.txt");
    std::string s;
    lexer* lex = initLexer("");
    while (std::cin >> s){
        if (s[0] == '@'){
            if (s == "@debug") turn_on_debug();
            if (s == "@precision"){
                int x;
                std::cin >> x;
                set_precision(x);
            }
        }else {
            updateLexer(lex, s);
            carryToToken(lex);
        }
    }
    return 0;
}

//func main : int -> int
//{
//int lol = 5;
//lol = lol + 5;
//return 0;
//}