#pragma once

#ifndef MAFFIN_LEXER_H
#define MAFFIN_LEXER_H

#include <string>
#include <tuple>
#include "token.h"

class lexer{
public:
    //set
    lexer(int pos, std::string src): pos(pos), src(src){}
    void setPosToZERO() { pos = 0; }
    void setSRC(const std::string& s) { src = s; }
    //get
    std::pair<char, bool> getCurChar(){ //char, error
        if (pos == src.length())
            return {0, false};
        char ch = src[pos];
        pos++;
        return {ch, true};
    }
private:
    int pos;
    std::string src;
};

lexer* initLexer(const std::string& src);
void updateLexer(lexer* lexer, std::string& src);
void carryToToken(lexer* lexer);
void sendToToken(const std::string& src);

#endif //MAFFIN_LEXER_H
