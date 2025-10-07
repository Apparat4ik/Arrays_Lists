#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T key;
    Node* left;
    Node* right;
    Node() : key(NULL), left(nullptr), right(nullptr){}
    Node(T value, Node* leftptr, Node* rightptr) : key(value), left(leftptr), right(rightptr){}
};

template<typename T>
struct DoubleList {
    Node<T>* head;
    Node<T>* tail;
    int size = 0;
    
    DoubleList() : head(nullptr), tail(head){}
    
    void destroy_list(Node<T>* head){
        while (size != 0){
            Node<T>* delNode = head;
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
Node<T>* get(DoubleList<T>& dl, T key){        // O(N)
    Node<T>* target = dl.head;
    while (target -> key != dl.key){
        target = target -> right;
    }
    return target;
}

template<typename T>
Node<T>* get_index(DoubleList<T>& dl,int index){
    Node<T>* ptr;
    
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
void get_key(DoubleList<T>& dl, int index){
    return get_index(dl, index) -> key;
}


template<typename T>
void add_next_node(DoubleList<T>& dl, int index, T key){    // O(1)
    try{
        Node<T>* ptr = get_index(dl, index);
        Node<T>* newNode = new Node<T>;
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
void add_prev_node(DoubleList<T>& dl,int index, T key){   // O(1)
    try{
        Node<T>* ptr = get_index(dl, index);
        Node<T>* newNode = new Node<T>;
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
void add_front(DoubleList<T>& dl, T key){        // O(1)
    Node<T>* newNode = new Node<T>;
    newNode -> key = key;
    newNode -> right = dl.head;
    dl.head -> left = newNode;
    newNode -> left = nullptr;
    dl.head = newNode;
    dl.size++;
    size_check(dl);
}

template<typename T>
void add_back(DoubleList<T>& dl,T key){       // O(1)
    Node<T>* newNode = new Node<T>;
    newNode -> key = key;
    newNode -> right = nullptr;
    dl.tail -> right = newNode;
    newNode -> left = dl.tail;
    dl.tail = newNode;
    dl.size++;
    size_check(dl);
}

template<typename T>
void create_DL(DoubleList<T>& dl, T keyBegin){
    dl.head = new Node<T>{keyBegin, nullptr, nullptr};
    dl.tail = dl.head;
    dl.size++;
}

template<typename T>
void delete_next_elem(DoubleList<T>& dl, int index){     // O(1)
    try{
        Node<T>* ptr = get_index(dl, index);
        Node<T>* deleteNode = ptr -> right;
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
void delete_prev_elem(DoubleList<T>& dl, int index){   //O(1)
    try{
        Node<T>* ptr = get_index(dl, index);
        Node<T>* deleteNode = ptr -> left;
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
void delete_front(DoubleList<T>& dl){              // O(1)
    Node<T>* deleteNode = dl.head;
    dl.head = dl.head -> right;
    dl.head -> left = nullptr;
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void delete_back(DoubleList<T>& dl){       // O(N)
    Node<T>* deleteNode = dl.tail;
    dl.tail = dl.tail -> left;
    dl.tail -> right = nullptr;
    delete deleteNode;
    dl.size--;
    size_check(dl);
}

template<typename T>
void delete_val(DoubleList<T>& dl, T key){      // O(N)
    Node<T>* deleteNode = dl.head;
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
void print_DL(const DoubleList<T>& dl) {
    Node<T>* ptr = dl.head;
    while (ptr) {
        cout << ptr -> key << ' ' << &(ptr -> key)<< " ";
        ptr = ptr -> right;
    }
    cout << endl;
}

template<typename T>
void print_DL_reverse(const DoubleList<T>& dl) {
    Node<T>* ptr = dl.tail;
    while (ptr) {
        cout << ptr -> key << " ";
        ptr = ptr -> left;
    }
    cout << endl;
}

