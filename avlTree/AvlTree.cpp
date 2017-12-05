#include "AvlTree.h"

using namespace std;

void print(int key, int balance){
    cout << "Added node: " << key << " with balance " << balance <<endl;
}

AvlTree::Node::Node(const int k): key(k), balance(0), left(nullptr), right(nullptr), parent(nullptr)  {
    print(key, balance);
}

AvlTree::Node::Node(const int k, int balanceN, Node *leftN, Node *rightN): key(k), balance(balanceN), left(leftN), right(rightN), parent(nullptr)  {
    print(key, balance);
};

AvlTree::Node::Node(const int k, int balanceN, Node *leftN, Node *rightN, Node *parentN): key(k), balance(balanceN), left(leftN), right(rightN), parent(parentN) {
    print(key, balance);
};


AvlTree::Node::~Node() {
    cout << "Deleted node: " << key << endl;
    delete left;
    delete right;
}

AvlTree::~AvlTree() {
    delete root;
}

const int AvlTree::getRootBalance() const { // TODO for testing
    return root->balance;
}


/********************************************************************
 * Search
 *******************************************************************/

bool AvlTree::search(const int key) const {
    if (root == nullptr){
        cout << "Tree is empty" << endl;
        return false;
    } else {
        return doSearch(root,key);
    }
}

bool AvlTree::doSearch(Node * node, const int key) const {
    if(node == nullptr){
        return false;
    } if(key < node->key){
        return doSearch(node->left,key);
    } else if(key > node->key ){
        return doSearch(node->right,key);
    } else {
        return true;
    }
}


/********************************************************************
 * Insert
 *******************************************************************/

void AvlTree::insert(const int key) {
    if(root == nullptr){
        root = new Node(key);
    } else {
        doInsert(root, key);
    }
}

void AvlTree::doInsert(Node * node, const int key) {
    if(node->key == key){
        cout << "Key " << key << " exist." << endl;

    } else {

        if(key < node->key){
            if(node->left != nullptr){
                doInsert(node->left,key);
            } else {
                node->left = new Node(key);

                // TODO
            }
        } else {
            if(node->right != nullptr){
                doInsert(node->right,key);
            } else {
                node->right = new Node(key);

                // TODO
            }
        }



    }
}

/********************************************************************
 * Traversal
 *******************************************************************/

vector<int> *AvlTree::preorder() const {
    if (root == nullptr)
        return nullptr;
    return root->preorder();
}

vector<int> *AvlTree::Node::preorder() const {
    auto vec = new vector<int>();
    // Wurzel in vec
    vec->push_back(key);
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->preorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->preorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::inorder() const {
    if (root == nullptr)
        return nullptr;
    return root->inorder();
}

vector<int> *AvlTree::Node::inorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->inorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->inorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    return vec;
}

vector<int> *AvlTree::postorder() const {
    if (root == nullptr)
        return nullptr;
    return root->postorder();
}

vector<int> *AvlTree::Node::postorder() const {
    auto vec = new vector<int>();
    // linken Nachfolger in vec
    if (left != nullptr) {
        auto left_vec = left->postorder();
        vec->insert(vec->end(), left_vec->begin(), left_vec->end());
    }
    // rechten Nachfolger in vec
    if (right != nullptr) {
        auto right_vec = right->postorder();
        vec->insert(vec->end(), right_vec->begin(), right_vec->end());
    }
    // Wurzel in vec
    vec->push_back(key);
    return vec;
}

