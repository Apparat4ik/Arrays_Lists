#pragma once

#include "List_header.h"

template<typename T>
struct QNode{
    T key;
    QNode<T>* next;
    
    QNode() : key(T()), next(nullptr){}
    QNode(T value, QNode* ptr) : key(value), next(ptr){}
};

template<typename T>
struct MyQueue{
    QNode<T>* head;
    QNode<T>* tail;
    int size = 0;
    
    MyQueue() : head(nullptr), tail(head){}
    
    void destroy_queue(QNode<T>* head){
        while (head){
            QNode<T>* delNode = head;
            head = head -> next;
            delete delNode;
        }
    }
    
    ~MyQueue(){
        destroy_queue(head);
    }
};


template<typename T>   // O(1)
void QPUSH(MyQueue<T>& q, T key){
    QNode<T>* newNode = new QNode<T>;
    newNode -> key = key;
    if (q.head == nullptr){
        q.head = newNode;
        newNode -> next = nullptr;
        q.tail = q.head;
    } else {
        q.tail -> next = newNode;
        newNode -> next = nullptr;
        q.tail = newNode;
    }
    q.size++;
}

template<typename T>  // O(1)
void QPOP(MyQueue<T>& q){
    QNode<T>* delNode = q.head;
    q.head = q.head -> next;
    delete delNode;
    q.size--;
}

template<typename T>
void PRINT(const MyQueue<T>& q) {
    QNode<T>* ptr = q.head;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> next;
    }
    cout << endl;
}

template<typename T>   // O(1)
T get_head(const MyQueue<T>& q){
    return q.head -> key;
}

template<typename T>
bool QEMPTY(const MyQueue<T>& q){
    if (q.head == nullptr){return true;}
    return false;
}

template<typename T>
void get_tail(const MyQueue<T>& q){
    return q.tail -> key;
}

template<typename T>
void queue_write_file(const MyQueue<T>& q, const string& filename){   // запись стека в файл
    ofstream file(filename);
    if (file.is_open()){
        file << q.size << ' ';
        QNode<T>* current = q.head;
        while (current) {
            file << current -> key << ' ';
            current = current->next;
        }
    }
    file.close();
}

template<typename T>
void queue_read_file(MyQueue<T>& q, const string& filename){   // чтение из файла
    q.destroy_queue(q.head);
    ifstream file(filename);
    if (is_file_empty(filename)){return;}
    q = MyQueue<T>();
    
    int listsize;
    file >> listsize;
    for (int i = 0; i < listsize; i++) {
        T data;
        file >> data;
        QPUSH(q, data);
    }
    file.close();
}
