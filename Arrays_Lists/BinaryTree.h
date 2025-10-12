#pragma once

#include "header.h"
#include "MyQueue.cpp"

template<typename T>
struct TreeNode{
    T key;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode() : key(T()), left(nullptr), right(nullptr){}
    TreeNode(T value, TreeNode* leftptr, TreeNode* rightptr) : key(value), left(leftptr), right(rightptr){}
};

template<typename T>
struct FBTree{
    TreeNode<T>* root;
    
    FBTree() : root(nullptr){}
    
    void destroy_tree(TreeNode<T>* tree_node) {
        if (tree_node != nullptr) {
            destroy_tree(tree_node -> left);
            destroy_tree(tree_node -> right);
            delete tree_node;
        }
    }
    
    ~FBTree(){
        destroy_tree(root);
    }
};

template<typename T>
bool preorder_search(const TreeNode<T>& root, T key){  // прямой обход для поиска элемента
    if (root != nullptr){
        if (root -> key != key){
            pre_order(root -> left);
            pre_order(root -> right);
        } else {return true;}
    }
}

template<typename T>
bool TISMEMBER(const FBTree<T>& tree, T key){   // поиск элементач
    return preorder_search(tree.root, key);
}


template<typename T>
void TINSERT(FBTree<T>& tree, T key){
    TreeNode<T>* newNode = new TreeNode<T>{key, nullptr, nullptr};
    if (tree.root == nullptr) {
        tree.root = newNode;
        return;
    }

    MyQueue<TreeNode<T>*> q;
    QPUSH(q, tree.root);

    while (!QEMPTY(q)) {
        TreeNode<T>* current = get_head(q);
        QPOP(q);

        if (current->left == nullptr) {
            current->left = newNode;
            return;
        }
        else {
            QPUSH(q, current->left);
        }
        if (current->right == nullptr) {
            current->right = newNode;
            return;
        }
        else {
            QPUSH(q, current->right);
        }
    }
}

template<typename T>
bool is_fullbinary(TreeNode<T>* current){
    if ((current -> left == nullptr) ^ (current -> right == nullptr) == 1){
        return false;
    } else if (!(current -> left == nullptr && current -> right == nullptr)){
        return is_fullbinary(current -> left) && is_fullbinary(current -> right);
    }
    return true;
    
}


// обходы дерева в глубину
template<typename T>
void pre_order(const TreeNode<T>* root){  // прямой обход
    if (root != nullptr){
        cout << root -> key << ' ';
        pre_order(root -> left);
        pre_order(root -> right);
    }
}

template<typename T>
void in_order(const TreeNode<T>* root){  // центрированный обход
    if (root != nullptr){
        in_order(root -> left);
        cout << root -> key << ' ';
        in_order(root -> right);
    }
}

template<typename T>
void post_order(const TreeNode<T>* root){  // обратный обход
    if (root != nullptr){
        post_order(root -> left);
        post_order(root -> right);
        cout << root -> key << ' ';
    }
}

template<typename T>
void PRINT_preorder(FBTree<T>& tree){
    pre_order(tree.root);
    cout << endl;
}

template<typename T>
void PRINT_inorder(FBTree<T>& tree){
    in_order(tree.root);
    cout << endl;
}

template<typename T>
void PRINT_postorder(FBTree<T>& tree){
    post_order(tree.root);
    cout << endl;
}

template<typename T>
void PRINT(const FBTree<T>& tree){    // вывод через обход в ширину (BFS)
    if (tree.root == nullptr){
        throw out_of_range("Tree is empty");
    }
    
    MyQueue<TreeNode<T>*> q;
    QPUSH(q, tree.root);
    
    while (!QEMPTY(q)) {
        TreeNode<T>* current = get_head(q);
        QPOP(q);
        
        cout << current -> key << ' ';
        if (current -> left != nullptr){
            QPUSH(q, current -> left);
        }
        if (current -> right != nullptr){
            QPUSH(q, current -> right);
        }
    }
    cout << endl;
}
