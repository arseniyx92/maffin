#pragma once

#ifndef MAFFIN_PARSER_H
#define MAFFIN_PARSER_H

#include "token.h"


class parser {

};

//class function{
//    void upload_into(const std::vector<std::string>& vars) {
//        for (std::string s:vars)
//            variables.push_back(s);
//    }
//    void execute(std::vector<std::string>& input_vars, std::vector<std::string>& output_vars){
//
//    }
//private:
//    int vertex_on_AST;
//    std::vector<std::string> variables;
//};

void print(int v, const std::vector<Node>& tree);
void print_vals(const std::vector<std::string>& a);
std::string genRndString(int len);
std::pair<std::vector<std::string>, std::vector<std::string> > go(int v, std::vector<Node>& tree, int p);
void getTokenTree(std::vector<Node> tree);


#endif //MAFFIN_PARSER_H
