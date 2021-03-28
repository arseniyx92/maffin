////
//// Created by Pro on 14/03/2021.
////
//
//#ifndef MAFFIN_HASHMAP_H
//#define MAFFIN_HASHMAP_H
//
//#include <iostream>
//#include <random>
//#include <ctime>
//
//std::mt19937_64 rnd(std::time(NULL));
//
//template <class T1, class T2>
//
//class HashMap {
//public:
//    //get
//    size_t getCapacity() { return SIZE; }
//    int getSIZE() { return elementsCounter; }
//    std::pair<long long, long long> getHashFuncs() { return {hashFunc1, hashFunc2}; }
//    //set
//    void generateNewHashMap(){
//        std::pair<T1, T2> residence[elementsCounter];
//        int pos = 0;
//        for (int i = 0; i < SIZE; ++i){
//            if (map[i]){
//                residence[pos] = map[i];
//                pos++;
//            }
//        }
//        rnd = std::mt19937_64(std::time(NULL));
//        hashFunc1 = rnd();
//        hashFunc2 = rnd();
//        SIZE = std::max(SIZE, (size_t)elementsCounter*2);
//        delete [] map;
//        std::pair<T1, T2> *map = new T[SIZE];
//        for (int i = 0; i < elementsCounter; ++i){
//            if ((int)(residence[i])*hashFunc1)
//            map[(int)(residence[i])*hashFunc1] = residence[i];
//        }
//    }
//    void insert(T x){
//
//    }
//private:
//    size_t SIZE = 151;
//    int elementsCounter = 0;
//    long long hashFunc1, hashFunc2;
//    std::pair<T1, T2> *map;
//};
//
//#include <unordered_map>
//
//#endif //MAFFIN_HASHMAP_H
