//
// Created by Pro on 27/03/2021.
//

#include "include/parser.h"
#include "include/imports.h"
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <random>
#include <ctime>

std::unordered_set<std::string> BUILTIN = {
        "print"
};

std::mt19937 rnd(std::time(NULL));

std::unordered_map<std::string, std::pair<bool, int> > VarsToType; // { name, {is var(true) or const(false), what type} }
/*
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
12 - func //link to the tree Node
13 - double
*/
std::unordered_map<std::string, int> intVars;
std::unordered_map<std::string, long double> doubleVars;
std::unordered_map<std::string, long long> longintVars;
//std::unordered_map<std::string, > elongVars;
//std::unordered_map<std::string, > charVars;
//std::unordered_map<std::string, > boolVars;
//std::unordered_map<std::string, > stringVars;
//std::unordered_map<std::string, > arrayVars;
//std::unordered_map<std::string, > listVars;
//std::unordered_map<std::string, > setVars;
//std::unordered_map<std::string, > mapVars;
//std::unordered_map<std::string, > hashSetVars;
//std::unordered_map<std::string, > hashMapVars;
std::unordered_map<std::string, int> funcVars;

void print(int v, int p, const std::vector<Node>& tree){
    for (int i:tree[v].children){
        print(i, p+1, tree);
        if (v == 0) std::cout << std::endl;
    }
    std::cout << tree[v].val << '(' << p << ')' << ' ';
}

void print_vals(const std::vector<std::string>& a){
    for (std::string x:a){
        switch(VarsToType[x].second){
            case 0:
                std::cout << intVars[x] << ' ';
                break;
            case 1:
                std::cout << longintVars[x] << ' ';
                break;
            case 13:
                std::cout << doubleVars[x] << ' ';
                break;
        }
    }
}

std::string genRndString(int len){
    std::string s = "+";
    for (int i = 0; i < len; ++i) {
        s += char(rnd() % 277);
    }
    return s;
}

#define vars tree[v].variables

//getting vector of constants and variables
std::vector<std::string> go(int v, int p, std::vector<Node>& tree){
    for (int j = 0; j < tree[v].children.size(); ++j){
        int i = tree[v].children[j];
        std::vector<std::string> cur;
        cur = go(i, v, tree);
        for (std::string x:cur)
            vars.push_back(x);
    }
    switch (tree[v].id){
        case 0:
        {
            if (vars.size() != 1) assert(false); // SHOULD BE CHANGED TO MULTIPLE DECLARATION
            if (VarsToType.count(vars[0])){ // IF ALREADY EXISTS
                std::cout << "FATAL: " << vars[0] <<  " ALREADY EXISTS" << std::endl;
                assert(false);
            }
            VarsToType[vars[0]].second = stoi(tree[v].val);
            VarsToType[vars[0]].first = true;
            switch (stoi(tree[v].val)){
                case 0:
                {
                    intVars[vars[0]] = 0;
                    break;
                }
                case 1:
                {
                    longintVars[vars[0]] = 0;
                    break;
                }
                case 13:
                {
                    doubleVars[vars[0]] = 0.;
                    break;
                }
                default:
                    assert(false);
            }
            return {vars[0]};
        }
        case 1:
        {
            if (tree[v].val == "="){
                if (p == -1 || tree[p].variables.size() != 1 || vars.size() != 1 ||
                    !VarsToType.count(vars[0]) || !VarsToType.count(tree[p].variables[0]) ||
                    VarsToType[vars[0]].second != VarsToType[tree[p].variables[0]].second){
                    if (!VarsToType.count(vars[0]) || !VarsToType.count(tree[p].variables[0])){
                        std::cout << "'=' - Variable is not declared" << std::endl;
                    }else if (VarsToType[vars[0]].second != VarsToType[tree[p].variables[0]].second){
                        std::cout << "'=' - Variables have another types" << std::endl;
                    }else if (tree[p].variables.size() != 1 || vars.size() != 1){
                        std::cout << "'=' - U wanna do '=' for multiple variables (it's not ready yet)" << std::endl;
                    }else{
                        std::cout << "'=' - something extremely bad happened" << std::endl;
                    }
                    assert(false);
                }
                switch (VarsToType[vars[0]].second){
                    case 0:
                    {
                        intVars[tree[p].variables[0]] = intVars[vars[0]];
                        break;
                    }
                    case 1:
                    {
                        longintVars[tree[p].variables[0]] = longintVars[vars[0]];
                        break;
                    }
                    case 13:
                    {
                        doubleVars[tree[p].variables[0]] = doubleVars[vars[0]];
                        break;
                    }
                    default:
                        assert(false);
                }
                if (VarsToType[vars[0]].first == false){
                    VarsToType.erase(vars[0]);
                    intVars.erase(vars[0]);
                }
                return {};
            }else if (tree[v].val == "+"){
                std::string firstStr, secondStr;
                if (vars.empty()){
                    std::cout << "FATAL: doesn't have enough elements to be composed (+)" << std::endl;
                    assert(false);
                }
                if (tree[p].variables.empty()){
                    if (vars.size() > 1){
                        std::cout << "'+x' problem, 'x' is more than 1 variable" << std::endl;
                        assert(false);
                    }
                    return {vars.back()};
                }
                firstStr = vars.back();
                secondStr = tree[p].variables.back();
                vars.pop_back();
                tree[p].variables.pop_back();
                switch (VarsToType[firstStr].second){
                    case 0:
                    {
                        int ans = intVars[firstStr]+intVars[secondStr];
                        if (firstStr[0] == '+'){
                            VarsToType.erase(firstStr);
                            intVars.erase(firstStr);
                        }
                        if (secondStr[0] == '+'){
                            VarsToType.erase(secondStr);
                            intVars.erase(secondStr);
                        }
                        std::string s = genRndString(5);
                        VarsToType[s] = {false, 0};
                        intVars[s] = ans;
                        return {s};
                    }
                    case 1:
                    {
                        long long ans = longintVars[firstStr]+longintVars[secondStr];
                        if (firstStr[0] == '+'){
                            VarsToType.erase(firstStr);
                            longintVars.erase(firstStr);
                        }
                        if (secondStr[0] == '+'){
                            VarsToType.erase(secondStr);
                            longintVars.erase(secondStr);
                        }
                        std::string s = genRndString(5);
                        VarsToType[s] = {false, 0};
                        longintVars[s] = ans;
                        return {s};
                    }
                    case 13:
                    {
                        long double ans = doubleVars[firstStr]+doubleVars[secondStr];
                        if (firstStr[0] == '+'){
                            VarsToType.erase(firstStr);
                            doubleVars.erase(firstStr);
                        }
                        if (secondStr[0] == '+'){
                            VarsToType.erase(secondStr);
                            doubleVars.erase(secondStr);
                        }
                        std::string s = genRndString(5);
                        VarsToType[s] = {false, 0};
                        doubleVars[s] = ans;
                        return {s};
                    }
                    default:
                        assert(false);
                }
            }else if (tree[v].val == "-"){
                std::string firstStr, secondStr;
                if (vars.empty()){
                    std::cout << "FATAL: doesn't have enough elements to be composed (+)" << std::endl;
                    assert(false);
                }
                if (tree[p].variables.empty()){
                    if (vars.size() > 1){
                        std::cout << "'-x' problem, 'x' is more than 1 variable" << std::endl;
                        assert(false);
                    }
                    // TODO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
//                    std::string s = genRndString(5);
//                    VarsToType[s] = {false, VarsToType[vars.back()].second};
//                    auto T = arr_from_type(VarsToType[vars.back()].second);
//                    T[s] = stoi(tree[v].val);
//                    return {s};
                }
                firstStr = tree[p].variables.back();
                secondStr = vars.back();
                vars.pop_back();
                tree[p].variables.pop_back();
                switch (VarsToType[firstStr].second){
                    case 0:
                    {
                        int ans = intVars[firstStr]-intVars[secondStr];
                        if (firstStr[0] == '+'){
                            VarsToType.erase(firstStr);
                            intVars.erase(firstStr);
                        }
                        if (secondStr[0] == '+'){
                            VarsToType.erase(secondStr);
                            intVars.erase(secondStr);
                        }
                        std::string s = genRndString(5);
                        VarsToType[s] = {false, 0};
                        intVars[s] = ans;
                        return {s};
                    }
                    case 1:
                    {
                        long long ans = longintVars[firstStr]-longintVars[secondStr];
                        if (firstStr[0] == '+'){
                            VarsToType.erase(firstStr);
                            longintVars.erase(firstStr);
                        }
                        if (secondStr[0] == '+'){
                            VarsToType.erase(secondStr);
                            longintVars.erase(secondStr);
                        }
                        std::string s = genRndString(5);
                        VarsToType[s] = {false, 0};
                        longintVars[s] = ans;
                        return {s};
                    }
                    case 13:
                    {
                        long double ans = doubleVars[firstStr]-doubleVars[secondStr];
                        if (firstStr[0] == '+'){
                            VarsToType.erase(firstStr);
                            doubleVars.erase(firstStr);
                        }
                        if (secondStr[0] == '+'){
                            VarsToType.erase(secondStr);
                            doubleVars.erase(secondStr);
                        }
                        std::string s = genRndString(5);
                        VarsToType[s] = {false, 0};
                        doubleVars[s] = ans;
                        return {s};
                    }
                    default:
                        assert(false);
                }
            }else if (tree[v].val == "("){
                if (p != -1 && BUILTIN.find(tree[p].variables.back()) != BUILTIN.end()){
                    if (tree[p].variables.back() == "print"){
                        print_vals(vars);
                        std::cout << std::endl;
                    }
                }else if (p != -1 && funcVars.count(tree[p].variables.back())){}
                return vars;
            }
        }
        case 2:
        {
            std::string s = genRndString(5);
            VarsToType[s] = {false, 0};
            intVars[s] = stoi(tree[v].val);
            return {s};
        }
        case 3:
        {
            std::string s = genRndString(5);
            VarsToType[s] = {false, 13};
            doubleVars[s] = stod(tree[v].val);
            return {s};
        }
        case 4:
        {
            return {tree[v].val};
        }
        default:
        {
            //std::cout << "UNKNOWN VAR" << std::endl;
            return {};
        }
    }
}

void getTokenTree(std::vector<Node> tree){
    if (check_debug()){
        print(0, 0, tree);
        std::cout << std::endl;
    }
    go(0, -1, tree);
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

//int ghjtj = 7+8-1;
//ghjtj = 9+ghjtj;