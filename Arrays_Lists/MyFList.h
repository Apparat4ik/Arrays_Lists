#pragma once

#include "List_header.h"

template<typename T>
struct FLNode {
    T key;
    FLNode* next;
    FLNode() : key(T()), next(nullptr){}
    FLNode(T value, FLNode* ptr) : key(value), next(ptr){}
};

template<typename T>
struct ForwardList {
    FLNode<T>* head;
    int size = 0;
    
    ForwardList() : head(nullptr){}
    
    void destroy_list(FLNode<T>* head){
        FLNode<T>* current = head;
        while (current != nullptr) {
            FLNode<T>* next = current->next;
            delete current;
            current = next;
        }
        size = 0;
    }
    
    ~ForwardList(){
        destroy_list(head);
    }
};


template<typename T>
FLNode<T>* FGET(ForwardList<T>& fl, T key){        // O(N)
    FLNode<T>* target = fl.head;
    while (target -> key != key){
        target = target -> next;
    }
    return target;
}

template<typename T>
FLNode<T>* FGET_index(ForwardList<T>& fl,int index){   // O(N)
    FLNode<T>* ptr = fl.head;
    if (index >= fl.size || index < 0){
        throw out_of_range("forward list index out of bounds");
    }
    for (int i = 0; i < index; i++){
        ptr = ptr -> next;
    }
    return ptr;
}

template<typename T>
T FGET_key(ForwardList<T>& fl, int index){
    try{
        return FGET_index(fl, index) -> key;
    } catch(const exception& error){
        cerr << error.what() << endl;
    }
    return NULL;
}

template<typename T>
void FPUSH_next(ForwardList<T>& fl, int index, T key){    // O(n)
    try{
        FLNode<T>* ptr = FGET_index(fl, index);
        FLNode<T>* newNode = new FLNode<T>;
        newNode -> key = key;
        newNode -> next = ptr -> next;
        ptr -> next = newNode;
        fl.size++;
    } catch(const exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void FPUSH_prev(ForwardList<T>& fl,int index, T key){    // O(1)
    FLNode<T>* nextNode = fl.head;
    FLNode<T>* prevNode;
    FLNode<T>* newNode = new FLNode<T>;
    for(int i = 0; i < index; i++){
        prevNode = nextNode;
        nextNode = nextNode -> next;
    }
    newNode -> key = key;
    prevNode -> next = newNode;
    newNode -> next = nextNode;
    fl.size++;
}

template<typename T>
void FPUSH_front(ForwardList<T>& fl, T key){        // O(1)
    FLNode<T>* newNode = new FLNode<T>;
    newNode -> key = key;
    newNode -> next = fl.head -> next;
    fl.head -> next = newNode;
    fl.size++;
}

template<typename T>
void FPUSH_back(ForwardList<T>& fl,T key){       // O(N)
    if (fl.head == nullptr){
        fl.head = new FLNode<T>{key, nullptr};
        fl.size++;
        return;
    }
    FLNode<T>* ptr = fl.head;
    while(ptr -> next){
        ptr = ptr -> next;
    }
    FLNode<T>* newNode = new FLNode<T>;
    newNode -> key = key;
    newNode -> next = nullptr;
    ptr -> next = newNode;
    fl.size++;
}

template<typename T>
void FDEL_next(ForwardList<T>& fl, int index){     // O(N)
    try{
        FLNode<T>* ptr = FGET_index(fl, index);
        FLNode<T>* deleteNode = ptr -> next;
        ptr -> next = deleteNode -> next;
        delete deleteNode;
        fl.size--;
    } catch(exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void FDEL_prev(ForwardList<T>& fl,int index){
    try{
        FLNode<T>* nextNode = fl.head;
        FLNode<T>* prevNode;
        for(int i = 0; i < index - 1; i++){
            prevNode = nextNode;
            nextNode = nextNode -> next;
        }
        prevNode -> next = nextNode -> next;
        fl.size--;
        delete nextNode;
    } catch(exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void FDEL_front(ForwardList<T>& fl){              // O(1)
    FLNode<T>* deleteNode = fl.head;
    fl.head = fl.head -> next;
    delete deleteNode;
    fl.size--;
}

template<typename T>
void FDEL_back(ForwardList<T>& fl){       // O(N)
    
    FLNode<T>* ptr = fl.head;
    while (ptr -> next -> next){
        ptr = ptr -> next;
    }
    FLNode<T>* deleteNode = ptr -> next;
    ptr -> next = nullptr;
    delete deleteNode;
    fl.size--;
}

template<typename  T>
void FDEL_val(ForwardList<T>& fl,T key){      // O(N)
    FLNode<T>* delNode = fl.head;
    FLNode<T>* prevNode;
    while (delNode -> key != key){
        prevNode = delNode;
        delNode = delNode -> next;
    }
    prevNode -> next = delNode -> next;
    delete delNode;
    fl.size--;
}

template<typename T>
void PRINT(const ForwardList<T>& fl) {
    FLNode<T>* ptr = fl.head;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> next;
    }
    cout << endl;
}

template<typename T>
void flist_write_file(const ForwardList<T>& fl, const string& filename){   // запись списка в файл
    ofstream file(filename);
    if (file.is_open()){
        file << fl.size << ' ';
        FLNode<T>* current = fl.head;
        while (current) {
            file << current -> key << ' ';
            current = current->next;
        }
    }
    file.close();
}

template<typename T>
void flist_read_file(ForwardList<T>& fl, const string& filename){   // чтение из файла
    fl.destroy_list(fl.head);
    ifstream file(filename);
    if (is_file_empty(filename)){return;}
    fl = ForwardList<T>();
    
    int listsize;
    file >> listsize;
    for (int i = 0; i < listsize; i++) {
        T data;
        file >> data;
        FPUSH_back(fl, data);
    }
    file.close();
}
