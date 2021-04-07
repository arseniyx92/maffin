#ifndef MAFFIN_STACK_H
#define MAFFIN_STACK_H

#include <iostream>
#include <string>
#include <cstring>
#include <cassert>

class stack {
public:
    stack() {
        size = 0;
        capacity = 2; //50
        arr = new std::string[capacity];
    }

    void increase_size(){
        std::string *new_arr = new std::string[2*capacity];
        memcpy(new_arr, arr, capacity);
        capacity *= 2;
        arr = new_arr;
    }

    void push_back(std::string val){
        if (size == capacity) increase_size();
        arr[size] = val;
        size++;
    }

    void pop_back(){
        if (size == 0){
            std::cout << "Deleting unexisting element" << std::endl;
            assert(false);
        }
        size--;
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

    int get_size() const{
        return size;
    }

    int get_capacity() const{
        return capacity;
    }
private:
    int capacity, size;
    std::string *arr;
};

#endif //MAFFIN_STACK_H
