#pragma once

#include "List_header.h"
#include "MyQueue.h"

const string branch_right = "|--- ";
const string branch_left = "|__ ";

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
    int size = 0;
    
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
        size = 0;
    }
};

template<typename T>
bool preorder_search(const TreeNode<T>* root, T key){  // прямой обход для поиска элемента
    if (root != nullptr) {
            if (root->key == key) {
                return true;
            }
        
            if (preorder_search(root->left, key)) {
                return true;
            }
            if (preorder_search(root->right, key)) {
                return true;
            }
        }
        return false;
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
        tree.size++;
        return;
    }

    TreeNode<T>* current = tree.root;

    while (current) {
        if (key > current->key) {
            if (current->right != nullptr) {
                current = current->right;
            } else {
                current->right = newNode;
                tree.size++;
                return;
            }
        } else if (key < current->key) {
            if (current->left != nullptr) {
                current = current->left;
            } else {
                current->left = newNode;
                tree.size++;
                return;
            }
        } else {
            delete newNode;
            return;
        }
    }
}

template<typename T>
bool TISFULL(TreeNode<T>* current){
    if ((current -> left == nullptr) ^ (current -> right == nullptr) == 1){
        return false;
    } else if ((current -> left == nullptr && current -> right == nullptr)){
        return TISFULL(current -> left) && TISFULL(current -> right);
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
void PRINT_BFS(const FBTree<T>& tree){    // вывод через обход в ширину (BFS)
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

template<typename T>
void print_tree_recursive(TreeNode<T>* node, const string& prefix, bool isLeft) {
    if (node != nullptr) {
        cout << prefix;
        cout << (isLeft ? branch_left : branch_right);
        cout << node->key << endl;
        print_tree_recursive(node->right, prefix + (isLeft ? "|   " : "    "), false);
        print_tree_recursive(node->left, prefix + (isLeft ? "|   " : "    "), true);
    }
}

template<typename T>
void PRINT(TreeNode<T>* root, const string& prefix = "", bool isLeft = true) {
    if (root == nullptr) return;
        
    cout << prefix;
    cout << (isLeft ? "├──" : "└──" );
    cout << root->key << endl;
    
    PRINT(root->left, prefix + (isLeft ? "│   " : "    "), true);
    PRINT(root->right, prefix + (isLeft ? "│   " : "    "), false);
}

template<typename T>
void pre_order_write_file(const TreeNode<T>* root, ofstream& file){
    if (root != nullptr){
        file << root -> key << ' ';
        pre_order_write_file(root -> left, file);
        pre_order_write_file(root -> right, file);
    }
}

template<typename T>
void tree_write_file(const FBTree<T>& tree, const string& filename){   // запись дерева в файл
    ofstream file(filename);
    if (file.is_open()){
        file << tree.size << ' ';
        pre_order_write_file(tree.root, file);
    }
    file.close();
}


template<typename T>
void tree_read_file(FBTree<T>& tree, const string& filename){   // чтение из файла
    tree.destroy_tree(tree.root);
    ifstream file(filename);
    if (is_file_empty(filename)){return;}
    tree = FBTree<T>();
    
    int listsize;
    file >> listsize;
    for (int i = 0; i < listsize; i++) {
        T data;
        file >> data;
        TINSERT(tree, data);
    }
    file.close();
}
