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
           data = (ArNode<T>*)malloc(other.capacity * sizeof(ArNode<T>));
           size = other.size;
           for (int i = 0; i < size; i++) {
               data[i] = other.data[i];
           }
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
    for (int i = index; i < ar.size - 1; i++){
        ar.data[i] = ar.data[i + 1];
    }
    ar.data[ar.size - 1].key = T();
    ar.size--;
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
    cout << endl;
}

template<typename T>
int MSIZE(const MyArray<T>& ar){
    return ar.size;
}

template<typename T>
void array_write_file(const MyArray<T>& ar, const string& filename){   // запись массива в файл
    ofstream file(filename);
    if (file.is_open()){
        file << ar.size << ' ';
        for (int i = 0; i < ar.size; i++){
            file << ar.data[i].key << ' ';
        }
    }
    file.close();
}

template<typename T>
void array_read_file(MyArray<T>& ar, const string& filename){   // чтение из файла
    free(ar.data);
    ar.size = 0;
    ar.data = (ArNode<T>*)malloc(ar.capacity * sizeof(ArNode<T>));
    ifstream file(filename);
    
    if (is_file_empty(filename)){return;}
    
    int listsize;
    file >> listsize;
    
    T value;
    while (file >> value && ar.size < listsize) {
        MPUSH_back(ar, value);
    }
    file.close();
}
