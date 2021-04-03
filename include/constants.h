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
    {',', 11},
    {';', ROW_SCOPE},
    {'~', GLOBAL_SCOPE}
};

Token function_token(12), int32_token(0), int64_token(1), unsigned_token(-1),\
elong_token(-1), float_token(13), return_token(100), array_token(6);

std::unordered_map<std::string, Token> KEY_WORDS = {
        {"func", function_token},
        {"return", return_token},
        {"int", int32_token},
        {"longint", int64_token},
        {"elong", elong_token},
        {"float", float_token},
        {"unsigned", unsigned_token},
        {"array", array_token}
};

#endif //MAFFIN_CONSTANTS_H
