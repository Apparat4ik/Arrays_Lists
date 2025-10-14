#pragma once

#include "header.h"


template<typename T>
struct DLNode {
    T key;
    DLNode* prev;
    DLNode* next;
    DLNode() : key(T()), prev(nullptr), next(nullptr){}
    DLNode(T value, DLNode* prevptr, DLNode* nextptr) : key(value), prev(prevptr), next(nextptr){}
};

template<typename T>
struct DoubleList {
    DLNode<T>* head;
    DLNode<T>* tail;
    int size = 0;
    
    DoubleList() : head(nullptr), tail(head){}
    
    void destroy_list(DLNode<T>* head){
        DLNode<T>* current = head;
        while (current != nullptr) {
            DLNode<T>* next = current->next;
            delete current;
            current = next;
        }
        size = 0;
    }
    
    ~DoubleList(){
        destroy_list(head);
    }
};


template<typename T>
void size_check(DoubleList<T>& dl){
    if (dl.size == 2){
        dl.tail = dl.head -> next;
    }
    if (dl.size == 1){
        dl.tail = dl.head;
    }
}

template<typename T>
DLNode<T>* LGET(DoubleList<T>& dl, T key){        // O(N)
    DLNode<T>* target = dl.head;
    while (target != nullptr && target->key != key){
        target = target -> next;
    }
    if (target == nullptr){
        throw invalid_argument("There is no element");
    }
    return target;
}

template<typename T>
DLNode<T>* LGET_index(DoubleList<T>& dl, int index){
    DLNode<T>* ptr;
    
    if (index > dl.size / 2){
        ptr = dl.tail;
        for (int i = dl.size - 1; i > index; i--){
            ptr = ptr -> prev;
        }
    } else if (index <= dl.size / 2) {
        ptr = dl.head;
        for (int i = 0; i < index; i++){
            ptr = ptr -> next;
        }
    } else {
        throw out_of_range("double list inex out of bouds");
    }
    return ptr;
}

template<typename T>
T LGET_key(DoubleList<T>& dl, int index){
    return LGET_index(dl, index) -> key;
}


template<typename T>
void LPUSH_next(DoubleList<T>& dl, int index, T key){    // O(1)
    try{
        DLNode<T>* ptr = LGET_index(dl, index);
        DLNode<T>* newNode = new DLNode<T>;
        newNode -> key = key;
        newNode -> next = ptr -> next;
        ptr -> next -> prev = newNode;
        ptr -> next = newNode;
        newNode -> prev = ptr;
        dl.size++;
        size_check(dl);
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LPUSH_prev(DoubleList<T>& dl,int index, T key){   // O(1)
    try{
        DLNode<T>* ptr = LGET_index(dl, index);
        DLNode<T>* newNode = new DLNode<T>;
        newNode -> key = key;
        newNode -> next = ptr;
        ptr -> prev -> next = newNode;
        newNode -> prev = ptr -> prev;
        ptr -> prev = newNode;
        dl.size++;
        size_check(dl);
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LPUSH_front(DoubleList<T>& dl, T key){        // O(1)
    DLNode<T>* newNode = new DLNode<T>;
    newNode->key = key;
    newNode->prev = nullptr;
    newNode->next = dl.head;
    if (dl.head != nullptr){
        dl.head->prev = newNode;
    } else {
        dl.tail = newNode;
    }
    dl.head = newNode;
    dl.size++;
    size_check(dl);
}

template<typename T>
void LPUSH_back(DoubleList<T>& dl,T key){       // O(1)
    DLNode<T>* newNode = new DLNode<T>;
    newNode->key = key;
    newNode->next = nullptr;

    if (dl.head == nullptr){
        newNode->prev = nullptr;
        dl.head = dl.tail = newNode;
    } else {
        newNode->prev = dl.tail;
        dl.tail->next = newNode;
        dl.tail = newNode;
    }
    dl.size++;
    size_check(dl);
}

template<typename T>
void LDEL_next(DoubleList<T>& dl, int index){     // O(1)
    try{
        DLNode<T>* ptr = LGET_index(dl, index);
        DLNode<T>* deleteNode = ptr -> next;
        if (deleteNode = dl.tail){
            ptr -> next = nullptr;
            dl.tail = ptr;
            delete deleteNode;
            dl.size--;
            size_check(dl);
            
        } else {
            ptr -> next = deleteNode -> next;
            ptr -> next -> prev = ptr;
            delete deleteNode;
            dl.size--;
            size_check(dl);
        }
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LDEL_prev(DoubleList<T>& dl, int index){   //O(1)
    try{
        DLNode<T>* ptr = LGET_index(dl, index);
        DLNode<T>* deleteNode = ptr -> prev;
        if (deleteNode == dl.head){
            dl.head = deleteNode -> next;
            dl.head -> prev = nullptr;
            delete deleteNode;
            dl.size--;
            size_check(dl);
            
        } else {
            deleteNode -> prev -> next = ptr;
            ptr -> prev = deleteNode -> prev;
            dl.size--;
            delete deleteNode;
            size_check(dl);
        }
    } catch (exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void LDEL_front(DoubleList<T>& dl){              // O(1)
    if (dl.head == nullptr) return;
    DLNode<T>* deleteNode = dl.head;
    dl.head = dl.head -> next;
    
    if (dl.head != nullptr){
        dl.head->prev = nullptr;
    } else {
        dl.tail = nullptr;
    }
    
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void LDEL_back(DoubleList<T>& dl){       // O(N)
    if (dl.tail == nullptr) return;  // список пуст

    DLNode<T>* deleteNode = dl.tail;

    if (dl.tail->prev != nullptr){
        dl.tail = dl.tail->prev;
        dl.tail->next = nullptr;
    } else {
        dl.head = nullptr;
        dl.tail = nullptr;
    }
    
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void LDEL_val(DoubleList<T>& dl, T key){      // O(N)
    DLNode<T>* deleteNode = dl.head;
    while (deleteNode -> key != key){
        deleteNode = deleteNode -> next;
    }
    deleteNode -> prev -> next = deleteNode -> next;
    deleteNode -> next -> prev = deleteNode -> prev;
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void PRINT(const DoubleList<T>& dl) {
    DLNode<T>* ptr = dl.head;
    while (ptr) {
        cout << ptr -> key << ' ' << &(ptr -> key)<< " ";
        ptr = ptr -> next;
    }
    cout << endl;
}

template<typename T>
void PRINT_reverse_dl(const DoubleList<T>& dl) {
    DLNode<T>* ptr = dl.tail;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> prev;
    }
    cout << endl;
}

template<typename T>
void dlist_write_file(const DoubleList<T>& dl, const string& filename){   // запись списка в файл
    ofstream file(filename);
    if (file.is_open()){
        file << dl.size << ' ';
        DLNode<T>* current = dl.head;
        while (current) {
            file << current -> key << ' ';
            current = current -> next;
        }
    }
    file.close();
}

template<typename T>
void dlist_read_file(DoubleList<T>& dl, const string& filename){   // чтение из файла
    dl.destroy_list(dl.head);
    ifstream file(filename);
    if (is_file_empty(filename)){return;}
    dl = DoubleList<T>();
    
    int listsize;
    file >> listsize;
    for (int i = 0; i < listsize; i++) {
        T data;
        file >> data;
        LPUSH_back(dl, data);
    }
    file.close();
}

