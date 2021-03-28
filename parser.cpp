//
// Created by Pro on 27/03/2021.
//

#include "include/parser.h"
#include "include/imports.h"
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <random>
#include <ctime>

std::unordered_set<std::string> BUILTIN = {
        "print"
};

std::mt19937 rnd(std::time(NULL));

std::unordered_map<std::string, int> VarsToType;
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

void print(int v, const std::vector<Node>& tree){
    for (int i:tree[v].children){
        print(i, tree);
        if (v == 0) std::cout << std::endl;
    }
    std::cout << tree[v].val << ' ';
}

void print_vals(const std::vector<std::string>& a){
    for (std::string x:a){
        switch(VarsToType[x]){
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

#define consts tree[v].constss
#define vars tree[v].varss
//getting vector of constants and variables
std::pair<std::vector<std::string>, std::vector<std::string> > go(int v, std::vector<Node>& tree, int p){
    for (int j = 0; j < tree[v].children.size(); ++j){
        int i = tree[v].children[j];
        std::pair<std::vector<std::string>, std::vector<std::string> > cur;
        cur = go(i, tree, v);
        for (std::string x:cur.first)
            consts.push_back(x);
        for (std::string x:cur.second)
            vars.push_back(x);
    }
    switch (tree[v].id){
        case 0:
        {
            if (vars.size() != 1 || consts.size() != 0) assert(false);
            VarsToType[vars[0]] = stoi(tree[v].val);
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
            return {{}, {vars[0]}};
        }
        case 1:
        {
            if (tree[v].val == "="){
                if (p == -1 || tree[p].varss.size() != 1 || tree[p].constss.size() != 0 ||
                    consts.size() != 1 || vars.size() != 0 ||
                    VarsToType[consts[0]] != VarsToType[tree[p].varss[0]]) assert(false);
                switch (VarsToType[consts[0]]){
                    case 0:
                    {
                        intVars[tree[p].varss[0]] = intVars[consts[0]];
                        break;
                    }
                    case 1:
                    {
                        longintVars[tree[p].varss[0]] = longintVars[consts[0]];
                        break;
                    }
                    case 13:
                    {
                        doubleVars[tree[p].varss[0]] = doubleVars[consts[0]];
                        break;
                    }
                    default:
                        assert(false);
                }
                VarsToType.erase(consts[0]);
                intVars.erase(consts[0]);
                return {{}, {}};
            }else if (tree[v].val == "+"){
                std::string firstStr, secondStr;
                firstStr = (consts.empty() ? vars[0] : consts[0]);
                secondStr = (tree[p].varss.empty() ? tree[p].constss[0] : tree[p].varss[0]);
                if (consts.empty()) vars.pop_back();
                else consts.pop_back();
                if (tree[p].constss.empty()) tree[p].varss.pop_back();
                else tree[p].constss.pop_back();
                switch (VarsToType[firstStr]){
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
                        VarsToType[s] = 0;
                        intVars[s] = ans;
                        return {{s}, {}};
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
                        VarsToType[s] = 0;
                        longintVars[s] = ans;
                        return {{s}, {}};
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
                        VarsToType[s] = 0;
                        doubleVars[s] = ans;
                        return {{s}, {}};
                    }
                    default:
                        assert(false);
                }
            }else if (tree[v].val == "-"){
                std::string firstStr, secondStr;
                firstStr = (tree[p].varss.empty() ? tree[p].constss[0] : tree[p].varss[0]);
                secondStr = (consts.empty() ? vars[0] : consts[0]);
                if (consts.empty()) vars.pop_back();
                else consts.pop_back();
                if (tree[p].constss.empty()) tree[p].varss.pop_back();
                else tree[p].constss.pop_back();
                switch (VarsToType[firstStr]){
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
                        VarsToType[s] = 0;
                        intVars[s] = ans;
                        return {{s}, {}};
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
                        VarsToType[s] = 0;
                        longintVars[s] = ans;
                        return {{s}, {}};
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
                        VarsToType[s] = 0;
                        doubleVars[s] = ans;
                        return {{s}, {}};
                    }
                    default:
                        assert(false);
                }
            }else if (tree[v].val == "("){
                if (p != -1 && BUILTIN.find(tree[p].varss.back()) != BUILTIN.end()){
                    if (tree[p].varss.back() == "print"){
                        print_vals(consts);
                        print_vals(vars);
                        std::cout << std::endl;
                    }
                }else if (p != -1 && funcVars.count(tree[p].varss.back())){}
                return {consts, vars};
            }
        }
        case 2:
        {
            std::string s = genRndString(5);
            VarsToType[s] = 0;
            intVars[s] = stoi(tree[v].val);
            return {{s}, {}};
        }
        case 3:
        {
            std::string s = genRndString(5);
            VarsToType[s] = 13;
            doubleVars[s] = stod(tree[v].val);
            return {{s}, {}};
        }
        case 4:
        {
            return {{}, {tree[v].val}};
        }
        default:
        {
            //std::cout << "UNKNOWN VAR" << std::endl;
            return {{}, {}};
        }
    }
}

void getTokenTree(std::vector<Node> tree){
    if (check_debug()){
        print(0, tree);
        std::cout << std::endl;
    }
    go(0, tree, -1);
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

//int ghjtj = 7+8-1;
//ghjtj = 9+ghjtj;