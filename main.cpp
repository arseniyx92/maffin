#include <iostream>
#include <fstream>
#include <string>
#include "include/lexer.h"
#include "include/imports.h"

int main(){
//    std::string filepath;
//    std::cout << "Enter filepath:" << std::endl;
//    std::cin >> filepath;
//    std::fstream file;
//    file.open(filepath);
//    if (!file.is_open()){
//        std::cout << "ERROR: no file with such filepath" << std::endl;
//        return 0;
//    }
//    file.close();
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

//@precision 9
//
//float lol=2.342;
//print(lol);
//~