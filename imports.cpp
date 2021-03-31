//
// Created by Pro on 28/03/2021.
//

#include "include/imports.h"


bool debug = false;
int precision = -1;

void turn_on_debug(){
    debug = true;
}

bool check_debug(){
    return debug;
}


void set_precision(int x){
    precision = x;
}

int get_precision(){
    return precision;
};