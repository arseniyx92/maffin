#pragma once

#ifndef MAFFIN_CONSTANTS_H
#define MAFFIN_CONSTANTS_H

#include <unordered_set>
#include <unordered_map>

const int GLOBAL_SCOPE = 5000;
const int ROW_SCOPE = 1000;

std::unordered_map<char, int> SPECIAL_CHARACTERS = { // MAYBE SET INSTEAD OF MAP
    {')', 0},
    {'(', 1},
    {'/', 2},
    {'*', 3},
    {'-', 4},
    {'+', 5},
    {'=', 6},
    {']', 7},
    {'[', 8},
    {'{', 9},
    {'}', 10},
    {';', ROW_SCOPE},
    {'~', GLOBAL_SCOPE}
};

Token function_token, int32_token, int64_token, unsigned_token, elong_token;

std::unordered_map<std::string, Token> KEY_WORDS = {
        {"func", function_token},
        {"int", int32_token},
        {"longint", int64_token},
        {"elong", elong_token},
        {"unsigned", unsigned_token}
};

#endif //MAFFIN_CONSTANTS_H
