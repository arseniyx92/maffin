//
// Created by Pro on 14/03/2021.
//

#include "include/parser.h"
#include "include/token.h"
#include <cassert>
#include <cctype>

const int GLOBAL_SCOPE = 5000;
const int ROW_SCOPE = 1000;

std::vector<std::pair<int, std::string> > cur_cmd;
int cnt = 1;
std::vector<int> rootsOfExpressions = {0};
std::vector<Node> tree = {Node(GLOBAL_SCOPE, "")};

void get_keyword(Token token){
    cur_cmd.push_back({0, std::to_string(token.get_id())});
}

void get_special_character(char ch){
    std::string s = "";
    s += ch;
    cur_cmd.push_back({1, s});
    if (ch == ';') run_row();
    if (ch == '~') flood_of();
}

void get_variables(std::string var){
    bool is_dec = true;
    bool is_float = false;
    for (char ch:var){
        if (ch == '.' && is_dec){
            is_dec = false;
            is_float = true;
        }else if (isalpha(ch)){
            is_dec = false;
            is_float = false;
            break;
        }
    }
    if (is_dec){
        cur_cmd.push_back({2, var});
    }else if (is_float){
        cur_cmd.push_back({3, var});
    }else{
        cur_cmd.push_back({4, var});
    }
}

void run_row(){
    bool in_chain = false;
    int cur_root = cnt;
    tree[rootsOfExpressions.back()].children.push_back(cnt);
    tree.push_back(Node(ROW_SCOPE, ""));
    rootsOfExpressions.push_back(cnt);
    cnt++;

    std::vector<int> expectations = {0, 4};
    for (const std::pair<int, std::string> x:cur_cmd){
        bool ok = false;
        for (int exp:expectations){
            if (x.first == exp) ok = true;
        }
        if (!ok) assert(false);
        switch (x.first){
            case 0:
            {
                if (in_chain) assert(false);
                tree.push_back(Node(x.first, x.second));
                tree[rootsOfExpressions.back()].children.push_back(cnt);
                tree.back().children.push_back(cnt+1);
                in_chain = true;
                cnt++;
                expectations = {4};
                if (stoi(x.second) < 10) expectations.push_back(0);
                break;
            }
            case 1:
            {
                if (x.second == ";"){
                    if (in_chain) assert(false);
                    if (tree[rootsOfExpressions.back()].val == "=") rootsOfExpressions.pop_back();
                    if (rootsOfExpressions.back() != cur_root) assert(false);
                    rootsOfExpressions.pop_back();
                    break;
                }
                if (x.second == "(" || x.second == "[" || x.second == "{"){
                    tree.push_back(Node(x.first, x.second));
                    if (in_chain) in_chain = false;
                    else tree[rootsOfExpressions.back()].children.push_back(cnt);
                    rootsOfExpressions.push_back(cnt);
                    cnt++;
                }else if(x.second == ")" || x.second == "]" || x.second == "}"){
                    if (in_chain) assert(false);
                    if (tree[rootsOfExpressions.back()].val == "=") rootsOfExpressions.pop_back();
                    if ((x.second == ")" && tree[rootsOfExpressions.back()].val == "(") ||
                        (x.second == "]" && tree[rootsOfExpressions.back()].val == "[") ||
                        (x.second == "}" && tree[rootsOfExpressions.back()].val == "{")){
                        rootsOfExpressions.pop_back();
                    }else{
                        assert(false);
                    }
                }else if (x.second == "="){
                    tree.push_back(Node(x.first, x.second));
                    if (in_chain) in_chain = false;
                    else tree[rootsOfExpressions.back()].children.push_back(cnt);
                    rootsOfExpressions.push_back(cnt);
                    cnt++;
                }else{
                    if (in_chain) assert(false);
                    tree.push_back(Node(x.first, x.second));
                    tree[rootsOfExpressions.back()].children.push_back(cnt);
                    tree.back().children.push_back(cnt+1);
                    in_chain = true;
                    cnt++;
                }
                expectations = {1, 2, 3, 4};
                break;
            }
            case 2:
            {
                tree.push_back(Node(x.first, x.second));
                if (in_chain){
                    in_chain = false;
                }else{
                    tree[rootsOfExpressions.back()].children.push_back(cnt);
                }
                cnt++;
                expectations = {1};
                break;
            }
            case 3:
            {
                tree.push_back(Node(x.first, x.second));
                if (in_chain){
                    in_chain = false;
                }else{
                    tree[rootsOfExpressions.back()].children.push_back(cnt);
                }
                cnt++;
                expectations = {1};
                break;
            }
            case 4:
            {
                tree.push_back(Node(x.first, x.second));
                if (in_chain){
                    in_chain = false;
                }else{
                    tree[rootsOfExpressions.back()].children.push_back(cnt);
                }
                cnt++;
                expectations = {1};
                break;
            }
            default:
                assert(false);
        }
    }
    cur_cmd.clear();
}

void flood_of(){
    getTokenTree(tree);
    //clear memory
    rootsOfExpressions.clear();
    rootsOfExpressions.shrink_to_fit();
    tree.clear();
    tree.shrink_to_fit();
}
