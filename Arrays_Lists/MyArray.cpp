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
    
    void init_array(int initial_cap) {
        data = (Node<T>*)malloc(initial_cap * sizeof(Node<T>));
        capacity = initial_cap;
    }
    
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
    
    void add_to_back(int key) {                 // O(1)
        if (size >= capacity){return;}
        data[size].key = key;
        size++;
    }
    
    void destroy_array() {
        free(data);
    }
    
    void add_to_index(int index, int key){        // O(N)
        for (int i = size - 1; i >= index; i--){
            data[i + 1] = data[i];
        }
        data[index].key = key;
        size++;
    }
    
    int get(int index){             // O(1)
        return data[index].key;
    }
    
    void pop_index(int index){       // O(N)
        for (int i = index; i < size; i++){
            data[i] = data[i++];
        }
        data[size - 1].key = NULL;
    }
    
    void swap(int index, int swapkey){
        data[index].key = swapkey;
    }
    
    void print(){
        for (int i = 0; i < size; i++) {
            cout << data[i].key << " ";
        }
    }
    
    int array_size(){
        return size;
    }
    
    ~MyArray(){
        destroy_array();
    }
};



/*
int main() {
    MyArray arr1;
    arr1.init_array(11);
    
    
    for (int i = 0; i < 10; i++) {
        arr1.add_to_back(i * 10);
    }
    
    MyArray arr2;
    arr2.init_array(11);
    arr2 = arr1;
    arr1.print();
    cout << endl;
    arr1.add_to_index(5, 67);
    
    arr1.print();
    cout << endl;
    arr2.print();
    
    return 0;
}*/
