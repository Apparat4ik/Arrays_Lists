#pragma once

#include "List_header.h"


template<typename T>
struct StNode{
    T key;
    StNode* next;
    
    StNode() : key(T()), next(nullptr){}
    StNode(T value, StNode* ptr) : key(value), next(ptr){}
};

template<typename T>
struct MyStack{
    StNode<T>* head = nullptr;
    size_t size = 0;
    
    MyStack() : head(nullptr){}
    
    MyStack(initializer_list<T> list) :
        size(list.size()) {
        for (auto item : list){
            if (head == nullptr){
                head = new StNode<T>(item, nullptr);
            } else {
                StNode<T>* newNode = new StNode{item, head};
                head = newNode;
            }
        }
    }
    
    void destroy_stack(){
        StNode<T>* current = head;
        while (current != nullptr) {
            StNode<T>* next = current->next;
            delete current;
            current = next;
        }
    }
    
    ~MyStack(){
        destroy_stack();
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
T SPOP(MyStack<T>& st){  
    StNode<T>* delNode = st.head;
    st.head = st.head -> next;
    T Nodekey = delNode -> key;
    delete delNode;
    st.size--;
    return Nodekey;
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
    st.destroy_stack();
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
