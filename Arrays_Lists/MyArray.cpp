#include <iostream>
#include <cstdlib>

using namespace std;

template<typename T>
struct Node {
    T key;
};

template<typename T>
struct MyArray {
    Node<T>* data;
    int size;
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
    
    ~MyArray(){
        free(data);
    }
};

template<typename T>
void init_array(int initial_cap, MyArray<T>& ar) {
    data = (Node<T>*)malloc(initial_cap * sizeof(Node<T>));
    ar.capacity = initial_cap;
}

template<typename T>
void add_to_back(MyArray<T>& ar, T key) {                 // O(1)
    if (size >= ar.capacity){return;}
     
    ar.size++;
}

template<typename T>
void add_to_index(MyArray<T>& ar, int index, T key){        // O(N)
    for (int i = ar.size - 1; i >= index; i--){
        ar.data[i + 1] = ar.data[i];
    }
    ar.data[index].key = key;
    ar.size++;
}

template<typename T>
T get(MyArray<T>& ar, int index){             // O(1)
    return ar.data[index].key;
}

template<typename T>
void pop_index(MyArray<T>& ar, int index){       // O(N)
    for (int i = index; i < ar.size; i++){
        ar.data[i] = ar.data[i++];
    }
    ar.data[ar.size - 1].key = NULL;
}

template<typename T>
void swap(MyArray<T>& ar,int index, T swapkey){
    ar.data[index].key = swapkey;
}

template<typename T>
void print(const MyArray<T>& ar){
    for (int i = 0; i < ar.size; i++) {
        cout << ar.data[i].key << " ";
    }
}

template<typename T>
int array_size(const MyArray<T>& ar){
    return ar.size;
}
