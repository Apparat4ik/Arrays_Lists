#include <iostream>

using namespace std;

template<typename T>
struct Node{
    T key;
    Node<T>* next;
    
    Node() : key(NULL), next(nullptr){}
    Node(T value, Node* ptr) : key(value), next(ptr){}
};

template<typename T>
struct MyQueue{
    Node<T>* head;
    Node<T>* tail;
    
    MyQueue() : head(nullptr), tail(head){}
    
    void destroy_queue(Node<T>* head){
        while (head){
            Node<T>* delNode = head;
            head = head -> next;
            delete delNode;
        }
    }
    
    ~MyQueue(){
        destroy_queue(head);
    }
};


template<typename T>   // O(1)
void push(MyQueue<T>& q, T key){
    Node<T>* newNode = new Node<T>;
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
    
}

template<typename T>  // O(1)
void pop(MyQueue<T>& q){
    Node<T>* delNode = q.head;
    q.head = q.head -> next;
    delete delNode;
}

template<typename T>
void print(const MyQueue<T>& q) {
    Node<T>* ptr = q.head;
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
bool empty(const MyQueue<T>& q){
    if (q.head == nullptr){return true;}
    return false;
}

template<typename T>
void get_tail(const MyQueue<T>& q){
    return q.tail -> key;
}
