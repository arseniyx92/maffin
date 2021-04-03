#pragma once

#ifndef MAFFIN_PARSER_H
#define MAFFIN_PARSER_H

#include "token.h"
#include "../structs/array/array.h"

class Function{
public:
    void upload_into(int v, const std::vector<std::string>& vars) {
        vertex_on_AST = v;
        for (std::string s:vars)
            variables.push_back(s);
    }
    int get_vertex() const{
        return vertex_on_AST;
    }
    std::vector<std::string> get_variables(){
        return variables;
    }
private:
    int vertex_on_AST;
    std::vector<std::string> variables;
};

class Scope{
public:
    bool finished = false;
    std::unordered_map<std::string, std::pair<bool, int> > VarsToType; // { name, {is var(true) or const(false), what type} }
    /*
    ------TYPES------
    0 - int,
    1 - longint,
    2 - elong,
    3 - char,
    4 - bool,
    5 - string,
    6 - array,
    7 - list,
    8 - set, //splay tree
    9 - map, //splay tree
    10 - hashSet
    11 - hashMap
    12 - func
    13 - double

    ------KEY_WORDS------
    100 - return
    */
    std::unordered_map<std::string, int> intVars;
    std::unordered_map<std::string, long double> doubleVars;
    std::unordered_map<std::string, long long> longintVars;
    //std::unordered_map<std::string, > elongVars;
    //std::unordered_map<std::string, > charVars;
    //std::unordered_map<std::string, > boolVars;
    //std::unordered_map<std::string, > stringVars;
    std::unordered_map<std::string, array> arrayVars;
    //std::unordered_map<std::string, > listVars;
    //std::unordered_map<std::string, > setVars;
    //std::unordered_map<std::string, > mapVars;
    //std::unordered_map<std::string, > hashSetVars;
    //std::unordered_map<std::string, > hashMapVars;
    std::unordered_map<std::string, Function> funcVars;
};

void print(int v, int p, const std::vector<Node>& tree);
void print_vals(const std::vector<std::string>& a, Scope& scope);
std::string genRndString(int len);
std::string copy_to_const(std::string s, Scope& scope);
std::vector<std::string> go(int v, int p, int what_child, std::vector<Node>& tree, Scope& scope);
void getTokenTree(std::vector<Node> tree);
std::string execute_function(Function& func, std::vector<Node>& tree, Scope& old_scope, std::vector<std::string>& input_vars);

#endif //MAFFIN_PARSER_H
