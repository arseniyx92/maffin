//INCLUDES

#include "include/parser.h"
#include "include/imports.h"
#include <iostream>
#include <cassert>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <random>
#include <ctime>
// TODO cash clearer
//LANGUAGE VITAL FUNCTIONS

std::string execute_function(Function& func, std::vector<Node>& tree, Scope& old_scope, std::vector<std::string>& input_vars){
    int vertex_on_AST = func.get_vertex();
    std::vector<std::string> variables = func.get_variables();
    //uploading scope
    Scope scope;
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
        case 12:
            scope.funcVars[ns] = scope.funcVars[s];
            break;
        case 13:
            scope.doubleVars[ns] = scope.doubleVars[s];
            break;
    }
    return ns;
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

std::unordered_set<std::string> BUILTIN = {
        "print", "set", "get", "sizeof"
};

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
        s += char(rnd() % 277);
    }
    return s;
}

std::vector<std::string> go(int v, int p, int what_child, std::vector<Node>& tree, Scope& scope){
    for (int j = 0; j < tree[v].children.size(); ++j){
        int i = tree[v].children[j];
        if (tree[i].val == "{"){
            if (j == 0 || tree[tree[v].children[j-1]].id != 0){
                std::cout << "FATAL: '{' not expected" << std::endl;
                assert(false);
            }
            continue;
        }
        std::vector<std::string> cur;
        cur = go(i, v, j, tree, scope);
        for (std::string x:cur)
            vars.push_back(x);
        if (finished){
            if (p != -1){
                tree[p].variables.clear();
                tree[p].variables.shrink_to_fit();
            }
            std::string result = vars[0];
            vars.clear();
            vars.shrink_to_fit();
            return {result};
        }
    }
    switch (tree[v].id){
        case 0:
        {
            if (vars.size() != 1) assert(false); // SHOULD BE CHANGED TO MULTIPLE DECLARATION
            if ((stoi(tree[v].val) < 100) && (VarsToType.count(vars[0]))){ // IF ALREADY EXISTS
                std::cout << "FATAL: " << vars[0] <<  " ALREADY EXISTS" << std::endl;
                assert(false);
            }
            if (stoi(tree[v].val) < 100) {
                VarsToType[vars[0]].second = stoi(tree[v].val);
                VarsToType[vars[0]].first = true;
            }
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
                case 6:
                {
                    arrayVars[vars[0]] = array();
                    break;
                }
                case 13:
                {
                    doubleVars[vars[0]] = 0.;
                    break;
                }
                case 12:
                {
                    if (tree[p].children.size() <= what_child+1){
                        std::cout << "FATAL: '{' Expected" << std::endl;
                        assert(false);
                    }
                    funcVars[vars.back()] = Function();
                    std::vector<std::string> a;
                    a.reserve(VarsToType.size());
                    for (const auto& s:VarsToType)
                        a.push_back(s.first);
                    funcVars[vars.back()].upload_into(tree[p].children[what_child+1], a);
                    break;
                }
                case 100:
                {
                    finished = true;
                    tree[p].variables.clear();
                    tree[p].variables.shrink_to_fit();
                    std::string result = vars[0];
                    vars.clear();
                    vars.shrink_to_fit();
                    return {result};
                }
                default:
                    assert(false);
            }
            std::string result = vars[0];
            vars.clear();
            vars.shrink_to_fit();
            return {result};
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
                vars.clear();
                vars.shrink_to_fit();
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
                    std::string result = vars.back();
                    vars.clear();
                    vars.shrink_to_fit();
                    return {result};
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
                        vars.clear();
                        vars.shrink_to_fit();
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
                        vars.clear();
                        vars.shrink_to_fit();
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
                        vars.clear();
                        vars.shrink_to_fit();
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
                    std::string s = genRndString(5);
                    VarsToType[s] = {false, VarsToType[vars.back()].second};
                    switch (VarsToType[vars.back()].second){
                        case 0: intVars[s] = -intVars[vars.back()];
                        case 1: longintVars[s] = -longintVars[vars.back()];
                        case 13: doubleVars[s] = -doubleVars[vars.back()];
                    }
                    vars.clear();
                    vars.shrink_to_fit();
                    return {s};
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
                        vars.clear();
                        vars.shrink_to_fit();
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
                        vars.clear();
                        vars.shrink_to_fit();
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
                        vars.clear();
                        vars.shrink_to_fit();
                        return {s};
                    }
                    default:
                        assert(false);
                }
            }else if (tree[v].val == "("){
                if (p != -1 && BUILTIN.find(tree[p].variables.back()) != BUILTIN.end()){
                    if (tree[p].variables.back() == "print"){
                        print_vals(vars, scope);
                        std::cout << std::endl;
                    }else if (tree[p].variables.back() == "set"){
                        switch (VarsToType[vars[0]].second){
                            case 6:
                            {
                                if (vars.size() != 3){
                                    std::cout << "FATAL: Incorrect number of parameters in SET function" << std::endl;
                                    assert(false);
                                }
                                if (VarsToType[vars[2]].second != 0){
                                    std::cout << "FATAL: Trying to change in " << tree[p].variables.back() << " array non 'int' index" << std::endl;
                                    assert(false);
                                }
                                std::string ns = copy_to_const(vars[1], scope);
                                arrayVars[vars[0]].set_value(ns, intVars[vars[2]]);
//                                arrayVars[vars[0]].set_value(vars[1], intVars[vars[2]]);
                            }
                        }
                        //clear cash TODO
                        vars = {};
                    }else if (tree[p].variables.back() == "get"){
                        std::string s;
                        switch (VarsToType[vars[0]].second){
                            case 6:
                            {
                                if (vars.size() != 2){
                                    std::cout << "FATAL: Incorrect number of parameters in GET function" << std::endl;
                                    assert(false);
                                }
                                if (VarsToType[vars[1]].second != 0){
                                    std::cout << "FATAL: Trying to get from " << tree[p].variables.back() << " array element with non 'int' index" << std::endl;
                                    assert(false);
                                }
                                s = arrayVars[vars[0]].get_value(intVars[vars[1]]);
                            }
                        }
                        //clear cash TODO
                        std::string ns = copy_to_const(s, scope);
                        vars = {ns};
                    }else if (tree[p].variables.back() == "sizeof"){
                        int size;
                        switch (VarsToType[vars[0]].second){
                            case 6:
                            {
                                if (vars.size() != 1){
                                    std::cout << "FATAL: Incorrect number of parameters in SIZEOF function" << std::endl;
                                    assert(false);
                                }
                                size = arrayVars[vars[0]].get_size();
                            }
                        }
                        std::string s = genRndString(5);
                        VarsToType[s] = {false, 0};
                        intVars[s] = size;
                        vars = {s};
                    }
                }else if (p != -1 && funcVars.count(tree[p].variables.back())){
                    std::string result = {execute_function(funcVars[tree[p].variables.back()], tree, scope, vars)};
                    tree[p].variables.pop_back();
                    vars.clear();
                    vars.shrink_to_fit();
                    return {result};
                }
                tree[p].variables.pop_back();
                std::vector<std::string> local = vars;
                vars.clear();
                vars.shrink_to_fit();
                return local;
            }else if (tree[v].val == "["){
                if (p != -1 && VarsToType[tree[p].variables.back()].second == 6){
                    if (VarsToType[vars.back()].second != 0){
                        std::cout << "FATAL: Trying to apply to " << tree[p].variables.back() << " array non 'int' size" << std::endl;
                        assert(false);
                    }
                    arrayVars[tree[p].variables.back()] = array(intVars[vars.back()]);
                }
                vars.clear();
                vars.shrink_to_fit();
                return {};
            }
        }
        case 2:
        {
            std::string s = genRndString(5);
            VarsToType[s] = {false, 0};
            intVars[s] = stoi(tree[v].val);
            vars.clear();
            vars.shrink_to_fit();
            return {s};
        }
        case 3:
        {
            std::string s = genRndString(5);
            VarsToType[s] = {false, 13};
            doubleVars[s] = stod(tree[v].val);
            vars.clear();
            vars.shrink_to_fit();
            return {s};
        }
        case 4:
        {
            vars.clear();
            vars.shrink_to_fit();
            return {tree[v].val};
        }
        default:
        {
            //std::cout << "UNKNOWN VAR" << std::endl;
            vars.clear();
            vars.shrink_to_fit();
            return {};
        }
    }
    vars.clear();
    vars.shrink_to_fit();
}

void getTokenTree(std::vector<Node> tree){
    if (check_debug()){
        print(0, 0, tree);
        std::cout << std::endl;
    }
    Scope scope;
    go(0, -1, 0, tree, scope);
    std::cout << std::endl;
    exit(EXIT_SUCCESS);
}

//int ghjtj = 7+8-1;
//ghjtj = 9+ghjtj;

//func lol {
//        a = a + 3;
//        return a;
//}
//
//int a = 2;
//lol(a);
//lol(a);
//print(a);
//~

//int glob = 3;
//
//func f
//        {
//                int new = u + 5;
//        return glob-new;
//        }
//
//int u = 50;
//print(f(u));
//print(u);
//u = f(u);
//print(u);
//~
