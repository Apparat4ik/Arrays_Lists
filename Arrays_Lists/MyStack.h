#pragma once

#include "header.h"


template<typename T>
struct StNode{
    T key;
    StNode* next;
    
    StNode() : key(T()), next(nullptr){}
    StNode(T value, StNode* ptr) : key(value), next(ptr){}
};

template<typename T>
struct MyStack{
    StNode<T>* head;
    int size = 0;
    
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
    st.size++;
}

template<typename T>  // O(1)
void SPOP(MyStack<T>& st){  // вернуть удаленный узел
    StNode<T>* delNode = st.head;
    st.head = st.head -> next;
    delete delNode;
    st.size--;
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

template<typename T>
void stack_write_file(const MyStack<T>& st, const string& filename){   // запись стека в файл
    ofstream file(filename);
    if (file.is_open()){
        file << st.size << ' ';
        StNode<T>* current = st.head;
        while (current) {
            file << current -> key << ' ';
            current = current->next;
        }
    }
    file.close();
}

template<typename T>
void stack_read_file(MyStack<T>& st, const string& filename){   // чтение из файла
    st.destroy_stack(st.head);
    ifstream file(filename);
    if (is_file_empty(filename)){return;}
    st = MyStack<T>();
    
    int listsize;
    file >> listsize;
    
    MyStack<T> tempStack;
    for (int i = 0; i < listsize; i++) {
        T data;
        file >> data;
        SPUSH(tempStack, data);
    }
   
    while (tempStack.head) {
        SPUSH(st, SGET_head(tempStack));
        SPOP(tempStack);
    }
       
    file.close();
}
