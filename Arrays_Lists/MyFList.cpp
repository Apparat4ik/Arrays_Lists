#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T key;
    Node* next;
    Node() : key(NULL), next(nullptr){}
    Node(T value, Node* ptr) : key(value), next(ptr){}
};

template<typename T>
struct ForwardList {
    Node<T>* head;
    int size = 0;
    
    ForwardList() : head(nullptr){}
    
    void destroy_list(Node<T>* head){
        while (size != 0){
            Node<T>* delNode = head;
            head = head -> next;
            size--;
            delete delNode;
        }
    }
    
    ~ForwardList(){
        destroy_list(head);
    }
};

template<typename T>
Node<T>* get(ForwardList<T>& fl, T key){        // O(N)
    Node<T>* target = fl.head;
    while (target -> key != fl.key){
        target = target -> next;
    }
    return target;
}

template<typename T>
Node<T>* get_index(ForwardList<T>& fl,int index){   // O(N)
    Node<T>* ptr = fl.head;
    if (index >= fl.size){
        throw out_of_range("forward list index out of bounds");
    }
    for (int i = 0; i < index; i++){
        ptr = ptr -> next;
    }
    return ptr;
}

template<typename T>
void get_key(ForwardList<T>& fl, int index){
    try{
        return get_index(fl, index) -> key;
    }
    catch(exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void add_next_node(ForwardList<T>& fl, int index, T key){    // O(1)
    try{
        Node<T>* ptr = get_index(fl, index);
        Node<T>* newNode = new Node<T>;
        newNode -> key = key;
        newNode -> next = ptr -> next;
        ptr -> next = newNode;
        fl.size++;
    } catch(exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void add_prev_node(ForwardList<T>& fl,int index, T key){    // O(1)
    Node<T>* nextNode = fl.head;
    Node<T>* prevNode;
    Node<T>* newNode = new Node<T>;
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
void add_front(ForwardList<T>& fl, T key){        // O(1)
    Node<T>* newNode = new Node<T>;
    newNode -> key = key;
    newNode -> next = fl.head -> next;
    fl.head -> next = newNode;
    fl.size++;
}

template<typename T>
void add_back(ForwardList<T>& fl,T key){       // O(N)
    Node<T>* ptr = fl.head;
    while(ptr -> next){
        ptr = ptr -> next;
    }
    Node<T>* newNode = new Node<T>;
    newNode -> key = key;
    newNode -> next = nullptr;
    ptr -> next = newNode;
    fl.size++;
}

template<typename T>
void delete_next_elem(ForwardList<T>& fl, int index){     // O(N)
    try{
        Node<T>* ptr = get_index(fl, index);
        Node<T>* deleteNode = ptr -> next;
        ptr -> next = deleteNode -> next;
        delete deleteNode;
        fl.size--;
    } catch(exception& error){
        cerr << error.what() << endl;
    }
}

template<typename T>
void delete_prev_elem(ForwardList<T>& fl,int index){
    try{
        Node<T>* nextNode = fl.head;
        Node<T>* prevNode;
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
void delete_front(ForwardList<T>& fl){              // O(1)
    Node<T>* deleteNode = fl.head;
    fl.head = fl.head -> next;
    delete deleteNode;
    fl.size--;
}

template<typename T>
void delete_back(ForwardList<T>& fl){       // O(N)
    Node<T>* ptr = fl.head;
    while (ptr -> next){
        ptr = ptr -> next;
    }
    Node<T>* deleteNode = ptr -> next;
    ptr -> next = nullptr;
    delete deleteNode;
    fl.size--;
}

template<typename T>
void delete_val(ForwardList<T>& fl,T key){      // O(N)
    Node<T>* delNode = fl.head;
    Node<T>* prevNode;
    while (delNode -> key != key){
        prevNode = delNode;
        delNode = delNode -> next;
    }
    prevNode -> next = delNode -> next;
    delete delNode;
    fl.size--;
}

template<typename T>
void print(const ForwardList<T>& fl) {
    Node<T>* ptr = fl.head;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> next;
    }
    cout << endl;
}

