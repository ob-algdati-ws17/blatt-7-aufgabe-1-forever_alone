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
        Node *parent = nullptr;
        Node(const int);
        Node(const int, Node * parent);
        ~Node();
        vector<int> *preorder() const;  // (Hauptreihenfolge)
        vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
        vector<int> *postorder() const; // (Nebenreihenfolge)
    };

    Node *root = nullptr;

    bool doInsert(Node *, const int);
    void upin(Node*);

    void doRemove(Node *);
    void upout(Node*);

    Node* doSearch(Node *, const int) const;

    void rotateRight(Node*);
    void rotateLeft(Node*);
public:
    ~AvlTree();

    bool search(const int) const;
    bool insert(const int);
    bool remove(const int);

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend ostream &operator<<(ostream &, const AvlTree &);

};
#endif //TREES_AVLTREE_H
