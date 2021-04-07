//
//#ifndef MAFFIN_LIST_H
//#define MAFFIN_LIST_H
//
//#include <string>
//#include <random>
//#include <cmath>
//#include <cstring>
//
//template<typename T>
//class list {
//public:
//    list(){
//        size = 50;
//        stock = new T[size*((int)log(size)+2)];
//        storey_sizes = new int[(int)log(size)+2];
//        for (int i = 0; i < sizeof(storey_sizes); ++i){
//            storey_sizes[i] = 0;
//        }
//    }
//    int get_capacity(){
//        return sizeof(stock);
//    }
//    T& access_cell(int storey, int index){
//        return stock[size*storey+index];
//    }
//    void increase_size(){
//        T *new_stock = new T[2*size*((int)log(2*size)+2)];
//        int *new_storey_sizes = new int[(int)log(2*size)+2];
//        memcpy(new_storey_sizes, storey_sizes, sizeof(storey_sizes));
//        for (int i = size; i < 2*size; ++i){
//            new_storey_sizes[i] = 0;
//        }
//        for (int i = 0; i < sizeof(storey_sizes); ++i){
//            for (int j = 0; j < storey_sizes[i]; ++j){
//                new_stock[i*size*2+j] = stock[i*size+j];
//            }
//        }
//        size *= 2;
//        stock = new_stock;
//        storey_sizes = new_storey_sizes;
//    }
//private:
//    int size;
//    //first storey - 0,1,2,...n-1, second - n,n+1,n+2,...2*n-1, third - 2*n,2*n+1,2*n+2,2*n+3, log(n) storey
//    T *stock;
//    int *storey_sizes;
//};
//
//std::mt19937 rnd(time(NULL));
//
//template <typename T>
//void insert(list<T>& list, int value, int position){
//    for (int i = 0; i < )
//}
//
//#endif //MAFFIN_LIST_H
