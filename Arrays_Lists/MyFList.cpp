#include <iostream>

using namespace std;

template<typename T>
struct Node {
    T key;
    Node* next;
    Node() : key(NULL), next(nullptr){}
    Node(int value, Node* ptr) : key(value), next(ptr){}
};

template<typename T>
struct ForwardList {
    Node<T>* head = new Node<T>{NULL, nullptr};
    int size = 0;
    
    Node<T>* get(int key){        // O(N)
        Node<T>* target = head;
        while (target -> key != key){
            target = target -> next;
        }
        return target;
    }
    
    Node<T>* get_index(int index){
        Node<T>* ptr = head;
        for (int i = 0; i < index; i++){
            ptr = ptr -> next;
        }
        return ptr;
    }
    
    void add_next_node(int index, int key){    // O(N)
        Node<T>* ptr = get_index(index);
        Node<T>* newNode = new Node<T>;
        newNode -> key = key;
        newNode -> next = ptr -> next;
        ptr -> next = newNode;
        size++;
    }
    
    void add_prev_node(int index, int key){
        Node<T>* nextNode = head;
        Node<T>* prevNode;
        Node<T>* newNode = new Node<T>;
        for(int i = 0; i < index; i++){
            prevNode = nextNode;
            nextNode = nextNode -> next;
        }
        newNode -> key = key;
        prevNode -> next = newNode;
        newNode -> next = nextNode;
        size++;
    }
    
    void add_front(int key){        // O(1)
        Node<T>* newNode = new Node<T>;
        newNode -> key = key;
        newNode -> next = head -> next;
        head -> next = newNode;
        size++;
    }
    
    void add_back(int key){       // O(N)
        Node<T>* ptr = head;
        for (int i = 0; i < size; i++){
            ptr = ptr -> next;
        }
        Node<T>* newNode = new Node<T>;
        newNode -> key = key;
        newNode -> next = nullptr;
        ptr -> next = newNode;
        size++;
    }

    void create_FL(int keyBegin){
        head = new Node<T>{keyBegin, nullptr};
    }

    void delete_next_elem(int index){     // O(N)
        Node<T>* ptr = get_index(index);
        Node<T>* deleteNode = ptr -> next;
        ptr -> next = deleteNode -> next;
        delete deleteNode;
        size--;
    }
    
    void delete_prev_elem(int index){
        Node<T>* nextNode = head;
        Node<T>* prevNode;
        for(int i = 0; i < index - 1; i++){
            prevNode = nextNode;
            nextNode = nextNode -> next;
        }
        prevNode -> next = nextNode -> next;
        size--;
        delete nextNode;
    }
    
    void delete_front(){              // O(1)
        Node<T>* deleteNode = head;
        head = head -> next;
        delete deleteNode;
        size--;
    }
    
    void delete_back(){       // O(N)
        Node<T>* ptr = head;
        for (int i = 0; i < size - 1; i++){
            ptr = ptr -> next;
        }
        Node<T>* deleteNode = ptr -> next;
        ptr -> next = nullptr;
        delete deleteNode;
        size--;
    }
    
    
    
    void delete_val(int key){      // O(N)
        Node<T>* delNode = head;
        Node<T>* prevNode;
        while (delNode -> key != key){
            prevNode = delNode;
            delNode = delNode -> next;
        }
        prevNode -> next = delNode -> next;
        delete delNode;
        size--;
    }
    
    void print() {
        Node<T>* ptr = head;
        while (ptr) {
            cout << ptr -> key << " ";
            ptr = ptr -> next;
        }
        cout << endl;
    }
    
    void destroy_list(Node<T>* head){
        size++;
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


int main(){
    ForwardList<int> fl;
    fl.create_FL(1);
    fl.add_back(2);
    fl.add_back(3);
    fl.add_next_node(0, 8);
    fl.delete_val(8);
    fl.add_prev_node(1, 9);
    fl.delete_prev_elem(2);
    fl.print();
    return 0;
}


