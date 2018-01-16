#include "AvlTree.h"
#include <functional>

#define BALANCE_MINUS_1 (-1)
#define BALANCE_0 0
#define BALANCE_PLUS_1 1

using namespace std;

AvlTree::Node::Node(const int k, Node *parentN): key(k), balance(0), left(nullptr), right(nullptr), parent(parentN)  {
    //cout << "Added node: " << key <<endl;
}

AvlTree::Node::~Node() {
    //cout << "Deleted node: " << key << endl;
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
        //cout << "Tree is empty" << endl;
        return false;
    } else {
        return (doSearch(root,key) != nullptr);
    }
}

AvlTree::Node* AvlTree::doSearch(Node * node, const int key) const {
    if(node == nullptr){
        return node;
    } if(key < node->key){
        return doSearch(node->left,key);
    } else if(key > node->key ){
        return doSearch(node->right,key);
    } else {
        return node;
    }
}

/********************************************************************
 * Insert
 *******************************************************************/

bool AvlTree::insert(const int key) {
    if(root == nullptr){
        root = new Node(key, nullptr);
        return true;
    } else {
        return doInsert(root, key);
    }
}

bool AvlTree::doInsert(Node * node, const int key) {
    if(node->key == key){
//        cout << "Key " << key << " exist." << endl;
        return false;
    }

    if(key < node->key){
        if(node->left != nullptr){
            return doInsert(node->left,key);

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
            return doInsert(node->right,key);

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
    return true;
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

int AvlTree::getBalance(const int key) const {
    Node* node = doSearch(root,key);
    if (!node){
//        cout << "Key " << key << " not exist";
        return -99; // Not found
    }
    return node->balance;
}

/********************************************************************
 * Rotation
 *******************************************************************/

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

    leftChild->parent = parent;
    leftChild->right = node;
    node->left = leftRightChild;
    node->parent = leftChild;

    if(leftRightChild){
        leftRightChild->parent = node;
    }
    setBalance(node);
    setBalance(leftChild);
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

    rightChild->parent = parent;
    rightChild->left = node;
    node->right = rightLeftChild;
    node->parent = rightChild;

    if(rightLeftChild){
        rightLeftChild->parent = node;
    }
    setBalance(node);
    setBalance(rightChild);
}


void AvlTree::setBalance(Node* node) {
    if(!node)  return;
    if (!node->left && !node->right)        node->balance = BALANCE_0;
    else if (node->left && node->right){
        int heightLeft = getHeight(node->left);
        int heightRight = getHeight(node->right);

        if(heightLeft > heightRight)        node->balance = BALANCE_MINUS_1;
        else if(heightLeft < heightRight)   node->balance = BALANCE_PLUS_1;
        else                                node->balance = BALANCE_0;
    }
    else if (!node->left)                   node->balance = BALANCE_PLUS_1;
    else                                    node->balance = BALANCE_MINUS_1;
}


int AvlTree::getHeight(Node * node) {
    if(node== nullptr)                          return 0;
    return 1 + max(getHeight(node->left), getHeight(node->right));
}

/********************************************************************
 * Remove
 *******************************************************************/

bool AvlTree::remove(const int key) {
    Node *node = doSearch(root, key);
    if(node == nullptr){
//        cout << "Key " << key << " do not exist." << endl;
        return false;
    }
    doRemove(node);
    return true;
}

void AvlTree::doRemove(Node *node) {
    if( !node->parent && !node->left && !node->right ){
        // 0. case -> I am the lonely root...
        delete(node);
        root = nullptr;
    } else if(!node->left && !node->right){
        // 1. case -> node is leaf
        doRemoveLeaf(node);
    } else if(!node->left){
        // 2. case -> node has only right child
        doRemoveNodeWithRightChild(node);
    } else if (!node->right){
        // 3. case -> node has only left child
        doRemoveNodeWithLeftChild(node);
    } else {
        // 4. case -> node has two children
        doRemove(swap(node));
    }
}

void AvlTree::doRemoveLeaf(Node *node) {
    Node *parent = node->parent;
    if(parent->left == node){   // node is left child
        parent->left = nullptr;
        if(parent->balance == BALANCE_MINUS_1){
            parent->balance = BALANCE_0;
            upout(parent);
        } else if(parent->balance == BALANCE_0){
            parent->balance = BALANCE_PLUS_1;
        } else { //BALANCE_PLUS_1
            Node* parentRight = parent->right;
            if(parentRight->balance == BALANCE_PLUS_1) {
                rotateLeft(parent);
                if(parentRight->balance == 0)
                    upout(parentRight);
            } else {
                rotateRight(parent->right);
                rotateLeft(parent);
                if(parent->parent->balance == 0)
                    upout(parent->parent);
            }

        }
    } else {                    // node is right child
        parent->right = nullptr;
        if(parent->balance == BALANCE_PLUS_1){
            parent->balance = BALANCE_0;
            upout(parent);
        } else if(parent->balance == BALANCE_0){
            parent->balance = BALANCE_MINUS_1;
        } else { //BALANCE_MINUS_1

            Node* parentLeft = parent->left;
            if(parentLeft->balance == BALANCE_MINUS_1){
                rotateRight(parent);
                if(parentLeft->balance == 0)
                    upout(parentLeft);
            } else{
                rotateLeft(parent->left);
                rotateRight(parent);
                if(parent->parent->balance == 0)
                    upout(parent->parent);
            }

        }
    }
    delete node;
}


void AvlTree::doRemoveNodeWithLeftChild(Node *node) {
    Node *parent = node->parent;
    node->left->parent = parent;
    if(!parent){
        root = node->left;
    } else if(parent->left == node){
        parent->left = node->left;
        upout(parent->left);
    } else {
        parent->right = node->left;
        upout(parent->right);
    }
    node->left = node->right = nullptr;
    delete node;
}


void AvlTree::doRemoveNodeWithRightChild(Node *node) {
    Node *parent = node->parent;
    node->right->parent = parent;
    if(!parent){
        root = node->right;
    } else if(parent->left == node){
        parent->left = node->right;
        upout(parent->left);
    } else {
        parent->right = node->right;
        upout(parent->right);
    }
    node->left = node->right = nullptr;
    delete node;
}

void AvlTree::upout(Node *node) {
    if(!node){
        return;
    }
    Node *parent = node->parent;
    if(!parent){
        node->balance = BALANCE_0;
        return;
    }

    if(parent->right == node){ // node is right child
        if(parent->balance == BALANCE_PLUS_1){
            parent->balance = BALANCE_0;
            upout(parent);
        } else if(parent->balance == BALANCE_0){
            parent->balance = BALANCE_MINUS_1;
        } else { //BALANCE_MINUS_1

            Node* leftChild = parent->left;
            if(leftChild->balance == BALANCE_0){
                rotateRight(parent);
            } else if(leftChild->balance == BALANCE_MINUS_1){
                rotateRight(parent);
                upout(leftChild);
            } else { // leftChild->balance == BALANCE_PLUS_1
                rotateLeft(leftChild);
                rotateRight(parent);
                upout(leftChild->parent);
            }
        }
    } else { // node is left child
        if(parent->balance == BALANCE_MINUS_1){
            parent->balance = BALANCE_0;
            upout(parent);
        } else if(parent->balance == BALANCE_0){
            parent->balance = BALANCE_PLUS_1;
        } else { //BALANCE_PLUS_1

            Node* rightChild = parent->right;
            if(rightChild->balance == BALANCE_0){
                rotateLeft(parent);
            } else if(rightChild->balance == BALANCE_PLUS_1){
                rotateLeft(parent);
                upout(rightChild);
            } else { // rightChild->balance == BALANCE_MINUS_1
                rotateRight(rightChild);
                rotateLeft(parent);
                upout(rightChild->parent);
            }
        }
    }
}


AvlTree::Node* AvlTree::swap(Node* node){ // TODO possible change - swap only key, not node
    Node* successor = node->right;
    while (successor->left){
        successor = successor->left;
    }
    Node* successorParent = successor->parent;
    Node* nodeRight = node->right;

    // swap balance
    int successorBalance = successor->balance;
    successor->balance = node->balance;
    node->balance = successorBalance;
    // swap parent
    if(node->parent){ // is node root?
        if(node->parent->left == node){
            node->parent->left = successor;
        } else {
            node->parent->right = successor;
        }
        successor->parent = node->parent;
    } else {
        root = successor;
        root->parent = nullptr;
    }

    //swap children
    successor->left = node->left;
    successor->left->parent = successor;
    node->right = successor->right;
    node->left = nullptr;
    if(successorParent != node){
        successorParent->left = node;
        successor->right = nodeRight;
        node->parent = successorParent;
        nodeRight->parent = successor;
    } else {
        node->parent = successor;
        successor->right = node;
    }
    return node;
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