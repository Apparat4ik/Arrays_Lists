#include <iostream>

using namespace std;

template<typename T>
struct Node{
    T key;
    Node* next;
    
    Node() : key(NULL), next(nullptr){}
    Node(T value, Node* ptr) : key(value), next(ptr){}
};

template<typename T>
struct MyStack{
    Node<T>* head;
    
    MyStack() : head(nullptr){}
    
    void destroy_stack(Node<T>* head){
        while (head){
            Node<T>* delNode = head;
            head = head -> next;
            delete delNode;
        }
    }
    
    ~MyStack(){
        destroy_stack(head);
    }
};


template<typename T>   // O(1)
void push(MyStack<T>& st, T key){
    Node<T>* newNode = new Node<T>;
    newNode -> key = key;
    newNode -> next = st.head;
    st.head = newNode;
}

template<typename T>  // O(1)
void pop(MyStack<T>& st){
    Node<T>* delNode = st.head;
    st.head = st.head -> next;
    delete delNode;
}

template<typename T>
void print(const MyStack<T>& st) {
    Node<T>* ptr = st.head;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> next;
    }
    cout << endl;
}

template<typename T>   // O(1)
T get_head(const MyStack<T>& st){
    return st.head -> key;
}
