#pragma once

#include "header.h"


template<typename T>
struct DLNode {
    T key;
    DLNode* left;
    DLNode* right;
    DLNode() : key(NULL), left(nullptr), right(nullptr){}
    DLNode(T value, DLNode* leftptr, DLNode* rightptr) : key(value), left(leftptr), right(rightptr){}
};

template<typename T>
struct DoubleList {
    DLNode<T>* head;
    DLNode<T>* tail;
    int size = 0;
    
    DoubleList() : head(nullptr), tail(head){}
    
    void destroy_list(DLNode<T>* head){
        while (size != 0){
            DLNode<T>* delNode = head;
            head = head -> right;
            size--;
            delete delNode;
        }
    }
    
    ~DoubleList(){
        destroy_list(head);
    }
};


template<typename T>
void size_check(DoubleList<T>& dl){
    if (dl.size == 2){
        dl.tail = dl.head -> right;
    }
    if (dl.size == 1){
        dl.tail = dl.head;
    }
}

template<typename T>
DLNode<T>* LGET(DoubleList<T>& dl, T key){        // O(N)
    DLNode<T>* target = dl.head;
    while (target -> key != dl.key){
        target = target -> right;
    }
    if (target == nullptr){
        throw invalid_argument("There is no element");
    }
    return target;
}

template<typename T>
DLNode<T>* LGET_index(DoubleList<T>& dl,int index){
    DLNode<T>* ptr;
    
    if (index > dl.size / 2){
        ptr = dl.tail;
        for (int i = dl.size - 1; i > index; i--){
            ptr = ptr -> left;
        }
    } else if (index <= dl.size / 2) {
        ptr = dl.head;
        for (int i = 0; i < index; i++){
            ptr = ptr -> right;
        }
    } else {
        throw out_of_range("double list inex out of bouds");
    }
    return ptr;
}

template<typename T>
void LGEt_key(DoubleList<T>& dl, int index){
    return get_index(dl, index) -> key;
}


template<typename T>
void LPUSH_next(DoubleList<T>& dl, int index, T key){    // O(1)
    try{
        DLNode<T>* ptr = get_index(dl, index);
        DLNode<T>* newNode = new DLNode<T>;
        newNode -> key = key;
        newNode -> right = ptr -> right;
        ptr -> right -> left = newNode;
        ptr -> right = newNode;
        newNode -> left = ptr;
        dl.size++;
        size_check(dl);
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LPUSH_prev(DoubleList<T>& dl,int index, T key){   // O(1)
    try{
        DLNode<T>* ptr = get_index(dl, index);
        DLNode<T>* newNode = new DLNode<T>;
        newNode -> key = key;
        newNode -> right = ptr;
        ptr -> left -> right = newNode;
        newNode -> left = ptr -> left;
        ptr -> left = newNode;
        dl.size++;
        size_check(dl);
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LPUSH_front(DoubleList<T>& dl, T key){        // O(1)
    DLNode<T>* newNode = new DLNode<T>;
    newNode -> key = key;
    newNode -> right = dl.head;
    dl.head -> left = newNode;
    newNode -> left = nullptr;
    dl.head = newNode;
    dl.size++;
    size_check(dl);
}

template<typename T>
void LPUSH_back(DoubleList<T>& dl,T key){       // O(1)
    DLNode<T>* newNode = new DLNode<T>;
    newNode -> key = key;
    newNode -> right = nullptr;
    dl.tail -> right = newNode;
    newNode -> left = dl.tail;
    dl.tail = newNode;
    dl.size++;
    size_check(dl);
}

template<typename T>
void LDEL_next(DoubleList<T>& dl, int index){     // O(1)
    try{
        DLNode<T>* ptr = get_index(dl, index);
        DLNode<T>* deleteNode = ptr -> right;
        ptr -> right = deleteNode -> right;
        ptr -> right -> left = ptr;
        delete deleteNode;
        dl.size--;
        size_check(dl);
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LDEL_prev(DoubleList<T>& dl, int index){   //O(1)
    try{
        DLNode<T>* ptr = get_index(dl, index);
        DLNode<T>* deleteNode = ptr -> left;
        deleteNode -> left -> right = ptr;
        ptr -> left = deleteNode -> left;
        dl.size--;
        delete deleteNode;
        size_check(dl);
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LDEL_front(DoubleList<T>& dl){              // O(1)
    DLNode<T>* deleteNode = dl.head;
    dl.head = dl.head -> right;
    dl.head -> left = nullptr;
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void LDEL_back(DoubleList<T>& dl){       // O(N)
    DLNode<T>* deleteNode = dl.tail;
    dl.tail = dl.tail -> left;
    dl.tail -> right = nullptr;
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void LDEL_val(DoubleList<T>& dl, T key){      // O(N)
    DLNode<T>* deleteNode = dl.head;
    while (deleteNode -> key != key){
        deleteNode = deleteNode -> right;
    }
    deleteNode -> left -> right = deleteNode -> right;
    deleteNode -> right -> left = deleteNode -> left;
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void PRINT(const DoubleList<T>& dl) {
    DLNode<T>* ptr = dl.head;
    while (ptr) {
        cout << ptr -> key << ' ' << &(ptr -> key)<< " ";
        ptr = ptr -> right;
    }
    cout << endl;
}

template<typename T>
void PRINT_reverse_dl(const DoubleList<T>& dl) {
    DLNode<T>* ptr = dl.tail;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> left;
    }
    cout << endl;
}

