#ifndef TREES_AVLTREE_H
#define TREES_AVLTREE_H

#include <iostream>
#include <vector>

using namespace std;

class AvlTree {

private:

    struct Node {
        const int key;
        int balance;
        Node *left = nullptr;
        Node *right = nullptr;
        Node *parent = nullptr; // TODO
        Node(const int);
        Node(const int, Node * parent);
        Node(const int, int balance, Node *left, Node *right);
        Node(const int, int balance, Node *left, Node *right, Node *parent);
        ~Node();
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;

    void doInsert(Node *, const int);
    void upin(Node* node);
    bool doSearch(Node *, const int) const;

    void rotateRight(Node*);
    void rotateLeft(Node*);
public:

    ~AvlTree();

    const int getRootBalance() const; // for testing

    bool search(const int) const;
    void insert(const int);
    void remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend ostream &operator<<(ostream &, const AvlTree &);

};
#endif //TREES_AVLTREE_H
