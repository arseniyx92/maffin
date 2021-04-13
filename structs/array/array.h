#pragma once

#ifndef MAFFIN_ARRAY_H
#define MAFFIN_ARRAY_H

#include <iostream>
#include <string>
#include <cassert>

class array {
public:
    array(int sz): size(sz){
        arr = new std::string[size];
    }
    array(){}

    int get_size() const{
        return size;
    }

    void set_value(std::string val, int pos){
        if (pos < size && pos >= 0) return void(arr[pos] = val);
        else{
            std::cout << "Index out of range: expected index < " << size << " but " << pos << " arrived" << std::endl;
            assert(false);
        }
    }

    std::string get_value(int pos){
        if (pos < size || pos < 0) return arr[pos];
        else{
            std::cout << "Index out of range: expected index < " << size << " but " << pos << " arrived" << std::endl;
            assert(false);
        }
    }
private:
    int size;
    std::string *arr;
};


#endif //MAFFIN_ARRAY_H
