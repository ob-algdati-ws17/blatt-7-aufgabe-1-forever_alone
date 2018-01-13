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
    void doRemoveLeaf(Node *);
    void doRemoveNodeWithLeftChild(Node *);
    void doRemoveNodeWithRightChild(Node *);
    void upout(Node*);
    Node* swap(Node*);

    Node* doSearch(Node *, const int) const;

    void rotateRight(Node*);
    void rotateLeft(Node*);
    void setBalance(Node*);
    int getHeight(Node*);
public:
    ~AvlTree();

    bool search(const int) const;
    bool insert(const int);
    bool remove(const int);

    void preOrderPrint()
    {
        preOrderPrint(root);

    }
    void preOrderPrint(struct Node *root)
    {
        if(root != NULL)
        {
            printf("%d ", root->key);
            preOrderPrint(root->left);
            preOrderPrint(root->right);
        }
    }

    vector<int> *preorder() const;  // (Hauptreihenfolge)
    vector<int> *inorder() const;   // (Symmetrische Reihenfolge)
    vector<int> *postorder() const; // (Nebenreihenfolge)

    friend ostream &operator<<(ostream &, const AvlTree &);

};
#endif //TREES_AVLTREE_H
