#include <iostream>
#include <fstream>
#include <string>
#include "include/lexer.h"
#include "include/imports.h"

int main() {
    std::string mode;
    std::cout << "From file(y) or from console(n): ";
    std::cin >> mode;
    if (mode == "y") {
        std::string filepath;
        std::cout << "Enter filepath: ";
        std::cin >> filepath;
        std::fstream file;
        file.open(filepath, std::ios::in);
        if (!file || !file.is_open()) {
            std::cout << "ERROR: no file with such filepath" << std::endl;
            return 0;
        }
        std::string s;
        lexer *lex = initLexer("");
        while (!file.eof()) {
            file >> s;
            if (s[0] == '@') {
                if (s == "@debug") turn_on_debug();
                if (s == "@precision") {
                    int x;
                    file >> x;
                    set_precision(x);
                }
            } else {
                updateLexer(lex, s);
                carryToToken(lex);
            }
        }
        file.close();
        s = "~";
        updateLexer(lex, s);
        carryToToken(lex);
    }else{
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