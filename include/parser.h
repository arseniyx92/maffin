#pragma once

#ifndef MAFFIN_PARSER_H
#define MAFFIN_PARSER_H

#include "token.h"
#include "../structs/array/array.h"
#include "../structs/stack/stack.h"
#include "../structs/skiplist/skiplist.h"

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
    int root = 0;
    std::vector<Node> PURE_TREE;
    bool go_into_curly = false;
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
    7 - skiplist,
    8 - stack,
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
    std::unordered_map<std::string, bool> boolVars;
    //std::unordered_map<std::string, > stringVars;
    std::unordered_map<std::string, array> arrayVars;
    std::unordered_map<std::string, stack> stackVars;
    std::unordered_map<std::string, skiplist<std::string> > skiplistVars;
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
std::string execute_function(Function& func, Scope& old_scope, std::vector<std::string>& input_vars);
bool compare(const std::string& val1, const std::string& val2, Scope& scope); // if first is smaller than second ? TRUE : FALSE


template <typename T>
std::string generate_const(const T& val, int type, Scope& scope){
    std::string s = genRndString(5);
    scope.VarsToType[s] = {false, type};
    switch (type) {
        case 0:
            scope.intVars[s] = val;
            break;
        case 1:
            scope.longintVars[s] = val;
            break;
        case 4:
            scope.boolVars[s] = val;
            break;
        case 13:
            scope.doubleVars[s] = val;
            break;
    }
    return s;
}

#endif //MAFFIN_PARSER_H
