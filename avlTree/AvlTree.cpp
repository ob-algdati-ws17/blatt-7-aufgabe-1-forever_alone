#include "AvlTree.h"

#define BALANCE_MINUS_1 -1
#define BALANCE_0 0
#define BALANCE_PLUS_1 1

using namespace std;


void print(int key, int balance){
    cout << "Added node: " << key << " with balance " << balance <<endl;
}

AvlTree::Node::Node(const int k): key(k), balance(0), left(nullptr), right(nullptr), parent(nullptr)  {
    print(key, balance);
}

AvlTree::Node::Node(const int k, Node *parentN): key(k), balance(0), left(nullptr), right(nullptr), parent(parentN)  {
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

const int AvlTree::getRootBalance() const {
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
                node->left = new Node(key, node);

                // TODO remove copyPaste from upin()
                if(node->balance == BALANCE_PLUS_1){
                    node->balance = BALANCE_0;
                } else if(node->balance == BALANCE_0){
                    node->balance = BALANCE_MINUS_1;
                    upin(node);

                } else { // BALANCE_MINUS_1
                    // TODO rotate
                    if(node->left->balance == BALANCE_MINUS_1){
                        //rotateRight(node);
                    } else if (node->left->balance == BALANCE_PLUS_1){
                        //rotateLeft(node);
                        //rotateRigth(node);
                    }
                }
            }

        } else {
            if(node->right != nullptr){
                doInsert(node->right,key);

            } else {
                node->right = new Node(key, node);

                if(node->balance == BALANCE_MINUS_1){
                    node->balance = BALANCE_0;
                } else if(node->balance == BALANCE_0){
                    node->balance = BALANCE_PLUS_1;
                    upin(node);

                } else {// BALANCE_PLUS_1
                    // TODO rotate
                    if(node->right->balance == BALANCE_PLUS_1){
                        //rotateLeft(node);
                    } else if (node->right->balance == BALANCE_PLUS_1){
                        //rotateRight(node);
                        //rotateLeft(node);
                    }
                }
            }
        }
    }
}

void AvlTree::upin(Node *node) {
    if(node == root){
        return;
    }

    if(node->parent->left == node){
        if(node->parent->balance == BALANCE_PLUS_1){
            node->parent->balance = BALANCE_0;
        } else if(node->parent->balance == BALANCE_0){
            node->parent->balance = BALANCE_MINUS_1;
            upin(node->parent);
        } else {

            if(node->balance == BALANCE_MINUS_1){
                //rotateRight(node->parent);
            } else if (node->balance == BALANCE_PLUS_1){
                //rotateLeft(node);
                //rotateRigth(node);
            }
        }

    } else {

        if(node->parent->balance == BALANCE_MINUS_1){
            node->parent->balance = BALANCE_0;
        } else if(node->parent->balance == BALANCE_0){
            node->parent->balance = BALANCE_PLUS_1;
            upin(node->parent);
        } else {

            if(node->balance == BALANCE_PLUS_1){
                //rotateLeft(node);
            } else if (node->balance == BALANCE_PLUS_1){
                //rotateRight(node);
                //rotateLeft(node);
            }
        }
    }
}


void AvlTree::rotateRight(Node *node) {

}

void AvlTree::rotateLeft(Node *node) {

}



/********************************************************************
 * Remove
 *******************************************************************/

void AvlTree::remove(const int key) {


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

