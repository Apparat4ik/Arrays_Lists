#pragma once

#include "header.h"


template<typename T>
struct StNode{
    T key;
    StNode* next;
    
    StNode() : key(NULL), next(nullptr){}
    StNode(T value, StNode* ptr) : key(value), next(ptr){}
};

template<typename T>
struct MyStack{
    StNode<T>* head;
    
    MyStack() : head(nullptr){}
    
    void destroy_stack(StNode<T>* head){
        while (head){
            StNode<T>* delNode = head;
            head = head -> next;
            delete delNode;
        }
    }
    
    ~MyStack(){
        destroy_stack(head);
    }
};


template<typename T>   // O(1)
void SPUSH(MyStack<T>& st, T key){
    StNode<T>* newNode = new StNode<T>;
    newNode -> key = key;
    newNode -> next = st.head;
    st.head = newNode;
}

template<typename T>  // O(1)
void SPOP(MyStack<T>& st){
    StNode<T>* delNode = st.head;
    st.head = st.head -> next;
    delete delNode;
}

template<typename T>
void PRINT(const MyStack<T>& st) {
    StNode<T>* ptr = st.head;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> next;
    }
    cout << endl;
}

template<typename T>   // O(1)
T SGET_head(const MyStack<T>& st){
    return st.head -> key;
}
