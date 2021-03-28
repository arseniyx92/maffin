#pragma once

#ifndef MAFFIN_PARSER_H
#define MAFFIN_PARSER_H

#include "token.h"


class parser {

};

void print(int v, const std::vector<Node>& tree);
void print_vals(const std::vector<std::string>& a);
std::string genRndString(int len);
std::pair<std::vector<std::string>, std::vector<std::string> > go(int v, std::vector<Node>& tree, int p);
void getTokenTree(std::vector<Node> tree);


#endif //MAFFIN_PARSER_H
