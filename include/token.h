#pragma once

#ifndef MAFFIN_TOKEN_H
#define MAFFIN_TOKEN_H

#include <iostream>
#include <string>
#include <map>
#include <tuple>
#include <unordered_map>
#include <vector>

class Node{
public:
    int id;
    std::string val;
    std::vector<int> children;
    Node(int id, std::string val): id(id), val(val){}
};

class Token {
public:
    int get_id(){
        return id;
    }
    Token(): id(228){}
private:
    int id;
};

void get_keyword(Token token);
void get_special_character(char ch);
void get_variables(std::string var);
void run_row();
void flood_of();


#endif //MAFFIN_TOKEN_H
