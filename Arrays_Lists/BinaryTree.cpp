#include <iostream>
#include "MyQueue.cpp"

using namespace std;

template<typename T>
struct TreeNode{
    T key;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode() : key(NULL), left(nullptr), right(nullptr){}
    TreeNode(T value, TreeNode* leftptr, TreeNode* rightptr) : key(value), left(leftptr), right(rightptr){}
};

template<typename T>
struct FBTree{
    TreeNode<T>* root;
    
};

template<typename T>
TreeNode<T>* insert(const FBTree<T>& tree, T key){
    TreeNode<T>* new_node = new TreeNode<T>{key, nullptr, nullptr};
    if (tree.root == nullptr) {
        tree.root = new_node;
        return;
    }

    MyQueue<TreeNode<T>*> q;
    push(q, tree.root);

    while (!q.empty()) {
        TreeNode<T>* current = get_head(q);
        pop(q);

        if (current->left == nullptr) {
            current->left = new_node;
            return;
        }
        else {
            push(q, current->left);
        }
        if (current->right == nullptr) {
            current->right = new_node;
            return;
        }
        else {
            push(q, current->right);
        }
    }
}

template<typename T>
bool isFull(TreeNode<T>& current){
    if (current -> left == nullptr ^ current -> right == nullptr == 1){return false;}
    isFull(current -> left);
    isFull(current -> right);
    return true;
}



int main(){
    
    return 0;
}
