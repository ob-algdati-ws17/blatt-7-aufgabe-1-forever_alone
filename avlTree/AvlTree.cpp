#include "AvlTree.h"
#include <functional>

#define BALANCE_MINUS_1 (-1)
#define BALANCE_0 0
#define BALANCE_PLUS_1 1

using namespace std;

AvlTree::Node::Node(const int k): key(k), balance(0), left(nullptr), right(nullptr), parent(nullptr)  {
    cout << "Added node: " << key <<endl;
}

AvlTree::Node::Node(const int k, Node *parentN): key(k), balance(0), left(nullptr), right(nullptr), parent(parentN)  {
    cout << "Added node: " << key <<endl;
}

AvlTree::Node::~Node() {
    cout << "Deleted node: " << key << endl;
    delete left;
    delete right;
}

AvlTree::~AvlTree() {
    delete root;
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
        return;
    }

    if(key < node->key){
        if(node->left != nullptr){
            doInsert(node->left,key);

        } else {
            node->left = new Node(key, node);
            if(node->balance == BALANCE_PLUS_1){
                node->balance = BALANCE_0;
            } else{
                node->balance = BALANCE_MINUS_1;
                upin(node);
            }
        }

    } else {
        if(node->right != nullptr){
            doInsert(node->right,key);

        } else {
            node->right = new Node(key, node);
            if(node->balance == BALANCE_MINUS_1){
                node->balance = BALANCE_0;
            } else {
                node->balance = BALANCE_PLUS_1;
                upin(node);
            }
        }
    }
}

void AvlTree::upin(Node *node) {
    if(node == root) return;
    Node* parent = node->parent;

    if(parent->left == node){

        if(parent->balance == BALANCE_PLUS_1){
            parent->balance = BALANCE_0;
        } else if(parent->balance == BALANCE_0){
            parent->balance = BALANCE_MINUS_1;
            upin(parent);
        } else {
            if(node->balance == BALANCE_MINUS_1){
                rotateRight(parent);
            } else {
                rotateLeft(node);
                rotateRight(parent);
            }
        }

    } else {

        if(parent->balance == BALANCE_MINUS_1){
            parent->balance = BALANCE_0;
        } else if(parent->balance == BALANCE_0){
            parent->balance = BALANCE_PLUS_1;
            upin(parent);
        } else {
            if(node->balance == BALANCE_PLUS_1){
                rotateLeft(parent);
            } else{
                rotateRight(node);
                rotateLeft(parent);
            }
        }
    }
}


void AvlTree::rotateRight(Node *node) {
    Node* parent = node->parent;
    Node* leftChild = node->left;
    Node* leftRightChild = leftChild->right;

    if (!parent){
        root = leftChild;
    } else if(parent->right == node){
        parent->right = leftChild;
    } else {
        parent->left = leftChild;
    }

    leftChild->balance = BALANCE_0;
    leftChild->parent = parent;
    leftChild->right = node;

    node->balance = BALANCE_0;
    node->left = leftRightChild;
    node->parent = leftChild;
    if(leftRightChild)
        leftRightChild->parent = node;
}

void AvlTree::rotateLeft(Node *node) {
    Node* parent = node->parent;
    Node* rightChild = node->right;
    Node* rightLeftChild = rightChild->left;

    if (!parent){
        root = rightChild;
    } else if(parent->right == node){
        parent->right = rightChild;
    } else {
        parent->left = rightChild;
    }

    rightChild->balance = BALANCE_0;
    rightChild->parent = parent;
    rightChild->left = node;

    node->balance = BALANCE_0;
    node->right = rightLeftChild;
    node->parent = rightChild;
    if(rightLeftChild)
        rightLeftChild->parent = node;
}

/********************************************************************
 * Remove
 *******************************************************************/

void AvlTree::remove(const int key) {
    if(root == nullptr){
        return;
    } else {
        doRemove(root, key);
    }
}


void AvlTree::doRemove(Node *node, const int key) {


}


void AvlTree::upout(Node *node) {


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

/********************************************************************
 * operator<<
 *******************************************************************/
std::ostream &operator<<(std::ostream &os, const AvlTree &tree) {
    function<void(std::ostream &, const int, const AvlTree::Node *, const string)> printToOs
            = [&](std::ostream &os, const int value, const AvlTree::Node *node, const string l) {

                static int nullcount = 0;

                if (node == nullptr) {
                    os << "    null" << nullcount << "[shape=point];" << endl;
                    os << "    " << value << " -> null" << nullcount
                       << " [label=\"" << l << "\"];" << endl;
                    nullcount++;
                } else {
                    os << "    " << value << " -> " << node->key
                       << " [label=\"" << l << "\"];" << endl;

                    printToOs(os, node->key, node->left, "l");
                    printToOs(os, node->key, node->right, "r");
                }
            };
    os << "digraph tree {" << endl;
    if (tree.root == nullptr) {
        os << "    null " << "[shape=point];" << endl;
    } else {
        printToOs(os, tree.root->key, tree.root->left, "l");
        printToOs(os, tree.root->key, tree.root->right, "r");
    }
    os << "}" << endl;
    return os;
}