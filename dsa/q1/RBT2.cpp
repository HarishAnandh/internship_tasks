#include <iostream>
#include <algorithm>

using namespace std;

template <typename T>
class RBT {
public:
    enum { RED, BLACK };

    RBT(const T &negInf) {
        nullnode = new Node();
        nullnode->left = nullnode->right = nullnode;
        nullnode->color = BLACK;

        header = new Node(negInf);
        header->left = header->right = nullnode;
        header->color = BLACK;
    }

    ~RBT() {
        makeEmpty(header->right);
        delete nullnode;
        delete header;
    }

    void insert(const T &x) {
        current = parent = grand = header;
        nullnode->data = x;

        while (current->data != x) {
            great = grand; grand = parent; parent = current;
            current = (x < current->data) ? current->left : current->right;

            if (current->left->color == RED && current->right->color == RED)
                handleReorient(x);
        }

        if (current != nullnode) return;

        current = new Node(x, nullnode, nullnode, RED);
        if (x < parent->data) parent->left = current;
        else parent->right = current;

        handleReorient(x);
    }

    void printTree() {
        if (header->right == nullnode) cout << "Tree is empty.";
        else inorder(header->right);
        cout << endl;
    }

private:
    struct Node {
        T data;
        Node *left, *right;
        int color;
        Node(const T &d = T(), Node *l = nullptr, Node *r = nullptr, int c = BLACK)
            : data(d), left(l), right(r), color(c) {}
    };

    Node *header, *current, *parent, *grand, *great, *nullnode;

    void handleReorient(const T &x) {
        current->color = RED;
        current->left->color = current->right->color = BLACK;

        if (parent->color == RED) {
            grand->color = RED;
            if ((x < grand->data) != (x < parent->data))
                parent = rotate(x, grand);
            current = rotate(x, great);
            current->color = BLACK;
        }
        header->right->color = BLACK;
    }

    Node* rotate(const T &x, Node *theParent) {
        if (x < theParent->data)
            return theParent->left = (x < theParent->left->data) ? RLC(theParent->left) : RRC(theParent->left);
        else
            return theParent->right = (x < theParent->right->data) ? RLC(theParent->right) : RRC(theParent->right);
    }

    Node* RLC(Node *&k2) {
        Node *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        return k1;
    }

    Node* RRC(Node *&k1) {
        Node *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        return k2;
    }

    void inorder(Node *t) {
        if (t != nullnode) {
            inorder(t->left);
            cout << t->data << (t->color == RED ? "(R) " : "(B) ");
            inorder(t->right);
        }
    }

    void makeEmpty(Node *&t) {
        if (t != nullnode) {
            makeEmpty(t->left);
            makeEmpty(t->right);
            delete t;
            t = nullnode;
        }
    }
};

int main() {
    RBT<int> tree(-9999);
    int choice, val;

    while (cin >> choice && choice != 5) {
        switch (choice) {
            case 1:
                if (cin >> val) tree.insert(val);
                break;
            case 2:
                tree.printTree();
                break;
        }
    }

    return 0;
}
