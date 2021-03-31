//
// Created by Pro on 14/03/2021.
//

#include "include/lexer.h"
#include "include/constants.h"

lexer* initLexer(const std::string& src){
    return new lexer(0, src);
}

void updateLexer(lexer* lexer, std::string& src){
    lexer->setPosToZERO();
    lexer->setSRC(src);
}

void carryToToken(lexer* lexer){
    std::string str = "";
    bool ok = true;
    do{
        char ch;
        std::tie(ch, ok) = lexer->getCurChar();
        if (ok){
            if (ch == ' ') {
                sendToToken(str);
                str = "";
            }else if (std::isalnum(ch) || std::isdigit(ch) || (ch == '.' && str.length() != 0 && std::isdigit(str[0]))){
                str += ch;
            }else{
                sendToToken(str);
                str = "";
                str += ch;
                sendToToken(str);
                str = "";
            }
        }
    }while (ok);
    sendToToken(str);
}

void sendToToken(const std::string& src){ //making from string containing a "token" token
    if (src == "") return;
    if (src.length() == 1){ //SPECIAL_CHARACTER
        if (SPECIAL_CHARACTERS.count(src[0])) get_special_character(src[0]);
        else get_variables(src);
    }else{
        if (KEY_WORDS.count(src)) get_keyword(KEY_WORDS[src]);
        else get_variables(src);
    }
}
