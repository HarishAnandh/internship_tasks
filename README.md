# internship_tasks


#include <iostream>
using namespace std;
enum Color { RED, BLACK };

template <typename T>
class RBtree {
private:
    struct Node {
        T data;
        Node *left, *right;
        Color color;

        Node(const T& d, Node* lt = nullptr, Node* rt = nullptr, Color c = BLACK)
            : data(d), left(lt), right(rt), color(c) {}
    };

    Node *header;   // Pseudo-root
    Node *nullNode; // Sentinel node
    Node *current, *parent, *grand, *great;

    // Helper to rotate nodes
    void rotate(const T& item, Node* theParent) {
        if (item < theParent->data)
            item < theParent->left->data ? 
                rotateWithLeftChild(theParent->left) : rotateWithRightChild(theParent->left);
        else
            item < theParent->right->data ? 
                rotateWithLeftChild(theParent->right) : rotateWithRightChild(theParent->right);
    }

    void rotateWithLeftChild(Node* &k2) {
        Node* k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2 = k1;
    }

    void rotateWithRightChild(Node* &k1) {
        Node* k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1 = k2;
    }

    void handleReorient(const T& item) {
        current->color = RED;
        current->left->color = BLACK;
        current->right->color = BLACK;

        if (parent->color == RED) {
            grand->color = RED;
            if ((item < grand->data) != (item < parent->data))
                parent = rotateWithItem(item, grand);
            current = rotateWithItem(item, great);
            current->color = BLACK;
        }
        header->right->color = BLACK; // Root is always black
    }

    Node* rotateWithItem(const T& item, Node* theParent) {
        if (item < theParent->data) {
            if (item < theParent->left->data)
                rotateWithLeftChild(theParent->left);
            else
                rotateWithRightChild(theParent->left);
            return theParent->left;
        } else {
            if (item < theParent->right->data)
                rotateWithLeftChild(theParent->right);
            else
                rotateWithRightChild(theParent->right);
            return theParent->right;
        }
    }

    void preorder(Node* t) const {
        if (t != nullNode) {
            cout << t->data << (t->color == RED ? "(R) " : "(B) ");
            preorder(t->left);
            preorder(t->right);
        }
    }

    int countNodes(Node* t, Color c) const {
        if (t == nullNode) return 0;
        int count = (t->color == c) ? 1 : 0;
        return count + countNodes(t->left, c) + countNodes(t->right, c);
    }

public:
    RBtree() {
        nullNode = new Node(T());
        nullNode->left = nullNode->right = nullNode;
        header = new Node(T(), nullNode, nullNode);
    }

    void insert(const T& x) {
        current = parent = grand = header;
        nullNode->data = x;

        while (current->data != x) {
            great = grand; grand = parent; parent = current;
            current = (x < current->data) ? current->left : current->right;

            if (current->left->color == RED && current->right->color == RED)
                handleReorient(x);
        }

        if (current != nullNode) return; // Already exists

        current = new Node(x, nullNode, nullNode, RED);
        if (x < parent->data) parent->left = current;
        else parent->right = current;
        handleReorient(x);
    }

    bool search(const T& x) {
        nullNode->data = x;
        Node* t = header->right;
        while (x != t->data)
            t = (x < t->data) ? t->left : t->right;
        return t != nullNode;
    }

    void display() {
        preorder(header->right);
        cout << endl;
    }

    void displayCounts() {
        cout << "Red Nodes: " << countNodes(header->right, RED) << endl;
        cout << "Black Nodes: " << countNodes(header->right, BLACK) << endl;
    }
};

int main() {
    RBtree<int> tree;
    int choice, val;

    do {
        cin >> choice;
        switch (choice) {
            case 1:
                int n; cout << "Enter number of elements: "; cin >> n;
                for(int i=0; i<n; i++) { cin >> val; tree.insert(val); }
                break;
            case 2:
                cout << "Enter value: "; cin >> val; tree.insert(val);
                break;
            case 3:
                cout << "Search for: "; cin >> val;
                cout << (tree.search(val) ? "Found" : "Not Found") << endl;
                break;
            case 4:
                tree.displayCounts();
                break;
            case 5:
                tree.display();
                break;
        }
    } while (choice != 6);
    return 0;
}
