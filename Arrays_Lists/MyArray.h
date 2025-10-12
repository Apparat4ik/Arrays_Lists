#pragma once

#include "header.h"
#include <cstdlib>

template<typename T>
struct ArNode {
    T key;
};

template<typename T>
struct MyArray {
    ArNode<T>* data;
    int size = 0;
    int capacity;
    
    MyArray() : data(nullptr), size(0), capacity(0){}
    
    MyArray(const MyArray& other) {    // конструктор для копирования массива
           init_array(other.capacity);
           size = other.size;
           for (int i = 0; i < size; i++) {
               data[i] = other.data[i];
           }
    }
       
    MyArray& operator=(const MyArray& other) {  // перешрузка оператора присваивания
        if (this != &other) {
            free(data);
            init_array(other.capacity);
            size = other.size;
            for (int i = 0; i < size; i++) {
                data[i] = other.data[i];
            }
        }
        return *this;
    }
    
    MyArray(int init_cap){
        data = (ArNode<T>*)malloc(init_cap * sizeof(ArNode<T>));
        capacity = init_cap;
    }
    
    ~MyArray(){
        free(data);
    }
};


template<typename T>
void MPUSH_back(MyArray<T>& ar, T key) {                 // O(1)
    if (ar.size >= ar.capacity){return;}
    ar.data[ar.size].key = key;
    ar.size++;
}

template<typename T>
void MPUSH_index(MyArray<T>& ar, int index, T key){        // O(N)
    if (index >= ar.size || index < 0){
        throw invalid_argument("Array index out od bounds");
    }
    
    for (int i = ar.size - 1; i >= index; i--){
        ar.data[i + 1] = ar.data[i];
    }
    ar.data[index].key = key;
    ar.size++;
}

template<typename T>
T MGET(MyArray<T>& ar, int index){             // O(1)
    if (index >= ar.size || index < 0){
        throw invalid_argument("Array index out od bounds");
    }
    return ar.data[index].key;
}

template<typename T>
void MDEL(MyArray<T>& ar, int index){       // O(N)
    if (index >= ar.size || index < 0){
        throw invalid_argument("Array index out od bounds");
    }
    for (int i = index; i < ar.size; i++){
        ar.data[i] = ar.data[i++];
    }
    ar.data[ar.size - 1].key = NULL;
}

template<typename T>
void MSWAP(MyArray<T>& ar,int index, T swapkey){
    if (index >= ar.size || index < 0){
        throw invalid_argument("Array index out od bounds");
    }
    ar.data[index].key = swapkey;
}

template<typename T>
void PRINT(const MyArray<T>& ar){
    for (int i = 0; i < ar.size; i++) {
        cout << ar.data[i].key << " ";
    }
}

template<typename T>
int MSIZE(const MyArray<T>& ar){
    return ar.size;
}
