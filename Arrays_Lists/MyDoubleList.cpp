/*#include <iostream>

using namespace std;

struct Node {
    int key;
    Node* previous;
    Node* next;
    Node() : key(NULL), next(nullptr), previous(nullptr){}
    Node(int value, Node* next_ptr, Node* prev_ptr) : key(value), next(next_ptr), previous(prev_ptr){}
};


struct ForwardList {
    Node* head;
    int size = 0;
    
    void add_next_node(int index, int key){    // O(N)
        Node* ptr = head;
        for (int i = 0; i < index; i++){
            ptr = ptr -> next;
        }
        Node* newNode = new Node;
        newNode -> key = key;
        newNode -> next = ptr -> next;
        ptr -> next = newNode;
        size++;
    }
    
    void add_front(int key){        // O(1)
        Node* newNode = new Node;
        newNode -> key = key;
        newNode -> next = head -> next;
        head -> next = newNode;
        size++;
    }
    
    void add_back(int key){       // O(N)
        Node* ptr = head;
        for (int i = 0; i < size; i++){
            ptr = ptr -> next;
        }
        Node* newNode = new Node;
        newNode -> key = key;
        newNode -> next = nullptr;
        ptr -> next = newNode;
        size++;
    }

    void create_FL(int keyBegin){
        head = new Node{keyBegin, nullptr};
    }

    void delete_next_elem(int index){     // O(N)
        Node* ptr = head;
        for (int i = 0; i < index; i++){
            ptr = ptr -> next;
        }
        Node* deleteNode = ptr -> next;
        ptr -> next = deleteNode -> next;
        delete deleteNode;
        size--;
    }
    
    void delete_front(){              // O(1)
        Node* deleteNode = head -> next;
        head -> next = deleteNode -> next;
        delete deleteNode;
        size--;
    }
    
    void delete_back(){       // O(N)
        Node* ptr = head;
        for (int i = 0; i < size; i++){
            ptr = ptr -> next;
        }
        Node* deleteNode = ptr -> next;
        ptr -> next = nullptr;
        delete deleteNode;
    }
    
    Node* get(int key){        // O(N)
        Node* target = head;
        while (target -> key != key){
            target = target -> next;
        }
        return target;
    }
    
    void delete_val(int key){      // O(N)
        Node* target = head;
        while (target -> key != key){
            target = target -> next;
        }
        delete target;
    }
    
    void print() {
        Node* ptr = head;
        while (ptr) {
            cout << ptr -> key << " ";
            ptr = ptr -> next;
        }
        cout << endl;
    }
};
*/


