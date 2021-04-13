#pragma once

#ifndef MAFFIN_SKIPLIST_H
#define MAFFIN_SKIPLIST_H

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <tuple>
#include <ctime>

template <typename T>
class skiplist {
public:
    int INF = 2e8;

    int _size = 1, capacity = 3;
    int max_storey = 3;

    struct Node{
        T key;
        std::vector<std::tuple<int, Node*, Node*> > storey; // dist till the next
    };

    using PNode = Node*;

    PNode init = new Node();

    inline void make_init(){
        for (int i = 0; i < max_storey; ++i){
            init->storey.emplace_back(INF, nullptr, nullptr);
        }
    }

    inline void put_in_front(PNode& left, PNode& current, int high, int dist){
        if (std::get<2>(left->storey[high])){
            auto right = std::get<2>(left->storey[high]);
            std::get<1>(right->storey[high]) = current;
            std::get<2>(current->storey[high]) = right;
            std::get<2>(left->storey[high]) = current;
            std::get<1>(current->storey[high]) = left;

            std::get<0>(current->storey[high]) = std::get<0>(left->storey[high])-dist+1;
            std::get<0>(left->storey[high]) = dist;
        }else{
            std::get<2>(left->storey[high]) = current;
            std::get<1>(current->storey[high]) = left;

            std::get<0>(left->storey[high]) = dist;
        }
    }

    inline void expand(){
        std::mt19937 rnd(time(NULL));
//        rnd = std::mt19937(time(NULL));
        capacity *= 2;
        max_storey++;
        init->storey.emplace_back(INF, nullptr, nullptr);
        auto prev = init;
        auto next = init;
        int dist = 0;
        auto distrib = std::uniform_int_distribution<int>(0, 1);
        while (std::get<2>(next->storey[max_storey-1]) != nullptr){
            if (distrib(rnd)) {
                dist += std::get<0>(next->storey[max_storey - 1]);
                std::get<2>(next->storey[max_storey - 1])->storey.emplace_back(INF, nullptr, nullptr);
                put_in_front(prev, std::get<2>(next->storey[max_storey - 1]), max_storey, dist);
                dist = 0;
                prev = std::get<2>(next->storey[max_storey-1]);
            }else{
                dist += std::get<0>(next->storey[max_storey - 1]);
            }
            next = std::get<2>(next->storey[max_storey-1]);
        }
    }

    inline void shrink(){
//        rnd = std::mt19937(time(NULL));
        max_storey--;
        capacity /= 2;
        auto next = init, next1 = init;
        while (std::get<2>(next->storey[max_storey]) != nullptr){
            next1 = std::get<2>(next->storey[max_storey]);
            next->storey.pop_back();
            next->storey.shrink_to_fit();
            next = next1;
        }
    }

    inline void dell(PNode& current){
        for (int high = 0; high < current->storey.size(); ++high){
            if (std::get<2>(current->storey[high])){
                auto left = std::get<1>(current->storey[high]);
                auto right = std::get<2>(current->storey[high]);
                std::get<1>(right->storey[high]) = left;
                std::get<2>(left->storey[high]) = right;
                std::get<0>(left->storey[high]) = std::get<0>(left->storey[high])+std::get<0>(current->storey[high])-1;
            }else{
                auto left = std::get<1>(current->storey[high]);
                std::get<2>(left->storey[high]) = nullptr;
                std::get<0>(left->storey[high]) = INF;
            }
        }
        delete current;
    }

    void insert(T x, int pos){
        pos++;
        std::mt19937 rnd(time(NULL));
        int dist = 0;
        auto next = init;
        std::vector<std::pair<int, PNode> > prev;
        for (int i = max_storey-1; i >= 0; --i){
            while (std::get<2>(next->storey[i]) && dist + std::get<0>(next->storey[i]) < pos){
                dist += std::get<0>(next->storey[i]);
                next = std::get<2>(next->storey[i]);
            }
            prev.emplace_back(pos-dist, next);
        }
        auto NewNode = new Node{x, {{INF, nullptr, nullptr}}};
        put_in_front(prev.back().second, NewNode, 0, prev.back().first); prev.pop_back();
        bool ok = true;
        auto distrib = std::uniform_int_distribution<int>(0, 1);
        for (int i = 1; i < max_storey; ++i){
            if (ok) ok = distrib(rnd);
            if (ok) {
                NewNode->storey.emplace_back(INF, nullptr, nullptr);
                put_in_front(prev.back().second, NewNode, i, prev.back().first);
                prev.pop_back();
            }else{
                if (std::get<2>(prev.back().second->storey[i])) std::get<0>(prev.back().second->storey[i])++;
                prev.pop_back();
            }
        }
        _size++;
        if (_size == capacity) expand();
    }

    void erase(int pos){
        pos++;
        int dist = 0;
        auto next = init;
        std::vector<std::pair<int, PNode> > prev;
        for (int i = max_storey-1; i >= 0; --i){
            while (std::get<2>(next->storey[i]) && dist + std::get<0>(next->storey[i]) <= pos){
                dist += std::get<0>(next->storey[i]);
                next = std::get<2>(next->storey[i]);
            }
            if (pos == dist) break;
            prev.emplace_back(i, next);
        }
        dell(next);
        for (auto& i:prev)
            std::get<0>(i.second->storey[i.first])--;
        _size--;
        if (_size*4 == capacity) shrink();
    }

    T find(int pos){
        pos++;
        int dist = 0;
        auto next = init;
        for (int i = max_storey-1; i >= 0; --i){
            if (pos == dist) break;
            while (std::get<2>(next->storey[i]) && dist + std::get<0>(next->storey[i]) <= pos){
                dist += std::get<0>(next->storey[i]);
                next = std::get<2>(next->storey[i]);
            }
        }
        return next->key;
    }

    void set_value(T x, int pos){
        pos++;
        int dist = 0;
        auto next = init;
        for (int i = max_storey-1; i >= 0; --i){
            if (pos == dist) break;
            while (std::get<2>(next->storey[i]) && dist + std::get<0>(next->storey[i]) <= pos){
                dist += std::get<0>(next->storey[i]);
                next = std::get<2>(next->storey[i]);
            }
        }
        next->key = x;
    }

    skiplist(){
        make_init();
    }
};


#endif //MAFFIN_SKIPLIST_H
