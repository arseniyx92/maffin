//
// Created by Pro on 27/03/2021.
//

#include "include/parser.h"
#include <iostream>

void print(int v, const std::vector<Node>& tree){
    for (int i:tree[v].children){
        print(i, tree);
        if (v == 0) std::cout << std::endl;
    }
    std::cout << tree[v].val << ' ';
}

void getTokenTree(std::vector<Node> tree){
    print(0, tree);
}