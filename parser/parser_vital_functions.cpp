//INCLUDES

#include "../include/parser.h"
#include "../include/imports.h"
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <random>
#include <ctime>

// TODO cash clearer

//LANGUAGE VITAL FUNCTIONS

std::string execute_function(Function& func, Scope& old_scope, std::vector<std::string>& input_vars){
    int vertex_on_AST = func.get_vertex();
    std::vector<std::string> variables = func.get_variables();
    //uploading scope
    Scope scope;
    scope.root = vertex_on_AST;
    scope.PURE_TREE = old_scope.PURE_TREE;
    std::vector<Node> tree = scope.PURE_TREE;
    std::vector<std::string> input_consts;
    input_consts.reserve(input_vars.size());
    array Args = array(input_vars.size());
    for (int i = 0; i < input_vars.size(); ++i){
        std::string ns = copy_to_const(input_vars[i], old_scope);
        Args.set_value(ns, i);
        input_consts.push_back(ns);
    }
    variables.reserve(variables.size()+input_consts.size());
    variables.insert(variables.end(), input_consts.begin(), input_consts.end());
    for (const std::string& s:variables){
        scope.VarsToType[s] = old_scope.VarsToType[s];
        switch (scope.VarsToType[s].second) {
            case 0:
                scope.intVars[s] = old_scope.intVars[s];
                break;
            case 1:
                scope.longintVars[s] = old_scope.longintVars[s];
                break;
            case 4:
                scope.boolVars[s] = old_scope.boolVars[s];
                break;
            case 12:
                scope.funcVars[s] = old_scope.funcVars[s];
                break;
            case 13:
                scope.doubleVars[s] = old_scope.doubleVars[s];
                break;
        }
    }
    if (scope.VarsToType.find("Args") != scope.VarsToType.end()){
        std::cout << "FATAL: using prohibited 'Args' variable that is already reserved" << std::endl;
        assert(false);
    }
    scope.VarsToType["Args"] = {true, 6};
    scope.arrayVars["Args"] = Args;
    //executing
    std::vector<std::string> output = go(vertex_on_AST, -1, 0, tree, scope);
    //deleting constants
    input_vars.reserve(input_vars.size()+input_consts.size());
    input_vars.insert(input_vars.end(), input_consts.begin(), input_consts.end());
    for (const std::string& s : input_vars){
        if (old_scope.VarsToType[s].first == false) {
            switch (old_scope.VarsToType[s].second) {
                case 0:
                    old_scope.intVars.erase(s);
                    break;
                case 1:
                    old_scope.longintVars.erase(s);
                    break;
                case 4:
                    old_scope.boolVars.erase(s);
                    break;
                case 12:
                    old_scope.funcVars.erase(s);
                    break;
                case 13:
                    old_scope.doubleVars.erase(s);
                    break;
            }
            old_scope.VarsToType.erase(s);
        }
    }
    //updating global scope variables (TODO: change stupid assignment of each element to something smarter)
    std::vector<std::string> initial_variables = func.get_variables();
    for (const std::string& s:initial_variables){
        switch (scope.VarsToType[s].second) {
            case 0:
                old_scope.intVars[s] = scope.intVars[s];
                break;
            case 1:
                old_scope.longintVars[s] = scope.longintVars[s];
                break;
            case 4:
                old_scope.boolVars[s] = scope.boolVars[s];
                break;
            case 12:
                old_scope.funcVars[s] = scope.funcVars[s];
                break;
            case 13:
                old_scope.doubleVars[s] = scope.doubleVars[s];
                break;
        }
    }
    //generating output
    if (!output.empty()) {
        std::string s = output.back();
        std::string ns = genRndString(5);
        old_scope.VarsToType[ns] = scope.VarsToType[s];
        switch (scope.VarsToType[s].second) {
            case 0:
                old_scope.intVars[ns] = scope.intVars[s];
                break;
            case 1:
                old_scope.longintVars[ns] = scope.longintVars[s];
                break;
            case 4:
                old_scope.boolVars[ns] = scope.boolVars[s];
                break;
            case 12:
                old_scope.funcVars[ns] = scope.funcVars[s];
                break;
            case 13:
                old_scope.doubleVars[ns] = scope.doubleVars[s];
                break;
        }
        return ns;
    }
    return "";
}

std::string copy_to_const(std::string s, Scope& scope){
    std::string ns = genRndString(5);
    scope.VarsToType[ns] = scope.VarsToType[s];
    switch (scope.VarsToType[s].second) {
        case 0:
            scope.intVars[ns] = scope.intVars[s];
            break;
        case 1:
            scope.longintVars[ns] = scope.longintVars[s];
            break;
        case 4:
            scope.boolVars[ns] = scope.boolVars[s];
            break;
        case 12:
            scope.funcVars[ns] = scope.funcVars[s];
            break;
        case 13:
            scope.doubleVars[ns] = scope.doubleVars[s];
            break;
    }
    return ns;
}

//template <typename T>
//std::string generate_const(const T& val, int type, Scope& scope){
//    std::string s = genRndString(5);
//    scope.VarsToType[val] = {false, type};
//    switch (type) {
//        case 0:
//            scope.intVars[s] = val;
//            break;
//        case 1:
//            scope.longintVars[s] = val;
//            break;
//        case 4:
//            scope.boolVars[s] = val;
//            break;
//        case 12:
//            scope.funcVars[s] = val;
//            break;
//        case 13:
//            scope.doubleVars[s] = val;
//            break;
//    }
//    return s;
//}

bool compare(const std::string& val1, const std::string& val2, Scope& scope){
    if (scope.VarsToType[val1].second != scope.VarsToType[val2].second){
        std::cout << "FATAL: comparing two variables with different types" << std::endl;
        assert(false);
    }
    switch (scope.VarsToType[val1].second) {
        case 0:
            return scope.intVars[val1] < scope.intVars[val2];
        case 1:
            return scope.longintVars[val1] < scope.longintVars[val2];
        case 4:
            return scope.boolVars[val1] < scope.boolVars[val2];
        case 13:
            return scope.doubleVars[val1] < scope.doubleVars[val2];
        default:
            std::cout << "FATAL: comparing incomparable type" << std::endl;
            assert(false);
    }
}

//DEFINES

#define vars tree[v].variables
#define finished scope.finished
#define VarsToType scope.VarsToType
#define intVars scope.intVars
#define doubleVars scope.doubleVars
#define longintVars scope.longintVars
#define elongVars scope.elongVars
#define charVars scope.charVars
#define boolVars scope.boolVars
#define stringVars scope.stringVars
#define arrayVars scope.arrayVars
#define listVars scope.listVars
#define setVars scope.setVars
#define mapVars scope.mapVars
#define hashSetVars scope.hashSetVars
#define hashMapVars scope.hashMapVars
#define funcVars scope.funcVars

std::mt19937 rnd(std::time(NULL));

void print(int v, int p, const std::vector<Node>& tree){
    for (int i:tree[v].children){
        print(i, p+1, tree);
        if (v == 0) std::cout << std::endl;
    }
    std::cout << tree[v].val << '(' << p << ')' << ' ';
}

void print_vals(const std::vector<std::string>& a, Scope& scope){
    for (std::string x:a){
        switch(VarsToType[x].second){
            case 0:
                std::cout << intVars[x] << ' ';
                break;
            case 1:
                std::cout << longintVars[x] << ' ';
                break;
            case 4:
                std::cout << boolVars[x] << ' ';
                break;
            case 13:
                if (get_precision() != -1)
                    std::cout.precision(get_precision());
                std::cout << doubleVars[x] << ' ';
                break;
        }
    }
}

std::string genRndString(int len){
    std::string s = "+";
    for (int i = 0; i < len; ++i) {
        s += char(rnd() % 150 + 10);
    }
    return s;
}