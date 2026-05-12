#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>

using namespace std;

// BOOK

struct Book {
    int id;
    string title;
    string author;
};

// BST NODE

struct BSTNode {
    Book book;
    BSTNode* left;
    BSTNode* right;

    BSTNode(Book b) {
        book = b;
        left = right = nullptr;
    }
};

//BST CLASS

class Problem1 {
private:
    BSTNode* root;

    BSTNode* insert(BSTNode* node, Book b) {

        if (node == nullptr)
            return new BSTNode(b);

        if (b.id < node->book.id)
            node->left = insert(node->left, b);

        else if (b.id > node->book.id)
            node->right = insert(node->right, b);

        return node;
    }

    BSTNode* search(BSTNode* node, int id, int& steps) {

        if (node == nullptr)
            return nullptr;

        steps++;

        if (node->book.id == id)
            return node;

        if (id < node->book.id)
            return search(node->left, id, steps);

        return search(node->right, id, steps);
    }

    void inorder(BSTNode* node) {

        if (node == nullptr)
            return;

        inorder(node->left);

        cout << "ID: " << node->book.id
             << " | Title: " << node->book.title
             << " | Author: " << node->book.author << endl;

        inorder(node->right);
    }

    BSTNode* findMin(BSTNode* node) {

        while (node->left != nullptr)
            node = node->left;

        return node;
    }

    BSTNode* deleteNode(BSTNode* node, int id) {

        if (node == nullptr)
            return nullptr;

        if (id < node->book.id)
            node->left = deleteNode(node->left, id);

        else if (id > node->book.id)
            node->right = deleteNode(node->right, id);

        else {

            // No Child

            if (node->left == nullptr &&
                node->right == nullptr) {

                delete node;
                return nullptr;
            }

            // One Child

            else if (node->left == nullptr) {

                BSTNode* temp = node->right;
                delete node;
                return temp;
            }

            else if (node->right == nullptr) {

                BSTNode* temp = node->left;
                delete node;
                return temp;
            }

            // Two Children

            BSTNode* temp = findMin(node->right);

            node->book = temp->book;

            node->right =
                deleteNode(node->right, temp->book.id);
        }

        return node;
    }

    void rangeSearch(BSTNode* node, int low, int high) {

        if (node == nullptr)
            return;

        if (node->book.id > low)
            rangeSearch(node->left, low, high);

        if (node->book.id >= low &&
            node->book.id <= high) {

            cout << node->book.id
                 << " - "
                 << node->book.title
                 << endl;
        }

        if (node->book.id < high)
            rangeSearch(node->right, low, high);
    }

    void closestID(BSTNode* node,
                   int target,
                   int& closest) {

        if (node == nullptr)
            return;

        if (abs(node->book.id - target)
            < abs(closest - target))

            closest = node->book.id;

        if (target < node->book.id)
            closestID(node->left, target, closest);

        else if (target > node->book.id)
            closestID(node->right, target, closest);
    }

    int height(BSTNode* node) {

        if (node == nullptr)
            return 0;

        return max(height(node->left),
                   height(node->right)) + 1;
    }

public:
    Problem1() {
        root = nullptr;
    }

    void insert(Book b) {
        root = insert(root, b);
    }

    void remove(int id) {
        root = deleteNode(root, id);
    }

    void display() {
        inorder(root);
    }

    void searchBook(int id) {

        int steps = 0;

        BSTNode* result = search(root, id, steps);

        if (result) {

            cout << "Book Found\n";
            cout << result->book.title << endl;
        }

        else {
            cout << "Book Not Found\n";
        }

        cout << "Steps = " << steps << endl;
    }

    void printRange(int low, int high) {
        rangeSearch(root, low, high);
    }

    void findClosest(int target) {

        if (root == nullptr) {
            cout << "Tree Empty\n";
            return;
        }

        int closest = root->book.id;

        closestID(root, target, closest);

        cout << "Closest ID = "
             << closest << endl;
    }

    int getHeight() {
        return height(root);
    }
};

//  AVL NODE

struct AVLNode {

    Book book;

    AVLNode* left;
    AVLNode* right;

    int height;

    AVLNode(Book b) {

        book = b;

        left = right = nullptr;

        height = 1;
    }
};

//AVL CLASS

class AVL {

private:
    AVLNode* root;

    int getHeight(AVLNode* node) {

        if (node == nullptr)
            return 0;

        return node->height;
    }

    int balanceFactor(AVLNode* node) {

        if (node == nullptr)
            return 0;

        return getHeight(node->left)
             - getHeight(node->right);
    }

    AVLNode* rightRotate(AVLNode* y) {

        AVLNode* x = y->left;
        AVLNode* T2 = x->right;

        x->right = y;
        y->left = T2;

        y->height =
            max(getHeight(y->left),
                getHeight(y->right)) + 1;

        x->height =
            max(getHeight(x->left),
                getHeight(x->right)) + 1;

        return x;
    }

    AVLNode* leftRotate(AVLNode* x) {

        AVLNode* y = x->right;
        AVLNode* T2 = y->left;

        y->left = x;
        x->right = T2;

        x->height =
            max(getHeight(x->left),
                getHeight(x->right)) + 1;

        y->height =
            max(getHeight(y->left),
                getHeight(y->right)) + 1;

        return y;
    }

    AVLNode* insert(AVLNode* node, Book b) {

        if (node == nullptr)
            return new AVLNode(b);

        if (b.id < node->book.id)
            node->left = insert(node->left, b);

        else if (b.id > node->book.id)
            node->right = insert(node->right, b);

        else
            return node;

        node->height =
            1 + max(getHeight(node->left),
                    getHeight(node->right));

        int balance = balanceFactor(node);

        // LL

        if (balance > 1 &&
            b.id < node->left->book.id)

            return rightRotate(node);

        // RR

        if (balance < -1 &&
            b.id > node->right->book.id)

            return leftRotate(node);

        // LR

        if (balance > 1 &&
            b.id > node->left->book.id) {

            node->left =
                leftRotate(node->left);

            return rightRotate(node);
        }

        // RL

        if (balance < -1 &&
            b.id < node->right->book.id) {

            node->right =
                rightRotate(node->right);

            return leftRotate(node);
        }

        return node;
    }

    AVLNode* minValueNode(AVLNode* node) {

        AVLNode* current = node;

        while (current->left != nullptr)
            current = current->left;

        return current;
    }

    AVLNode* deleteNode(AVLNode* root,
                        int id) {

        if (root == nullptr)
            return root;

        if (id < root->book.id)
            root->left =
                deleteNode(root->left, id);

        else if (id > root->book.id)
            root->right =
                deleteNode(root->right, id);

        else {

            if (root->left == nullptr ||
                root->right == nullptr) {

                AVLNode* temp =
                    root->left ?
                    root->left :
                    root->right;

                if (temp == nullptr) {

                    temp = root;
                    root = nullptr;
                }

                else {
                    *root = *temp;
                }

                delete temp;
            }

            else {

                AVLNode* temp =
                    minValueNode(root->right);

                root->book = temp->book;

                root->right =
                    deleteNode(root->right,
                               temp->book.id);
            }
        }

        if (root == nullptr)
            return root;

        root->height =
            1 + max(getHeight(root->left),
                    getHeight(root->right));

        int balance = balanceFactor(root);

        // LL

        if (balance > 1 &&
            balanceFactor(root->left) >= 0)

            return rightRotate(root);

        // RR

        if (balance < -1 &&
            balanceFactor(root->right) <= 0)

            return leftRotate(root);

        // LR

        if (balance > 1 &&
            balanceFactor(root->left) < 0) {

            root->left =
                leftRotate(root->left);

            return rightRotate(root);
        }

        // RL

        if (balance < -1 &&
            balanceFactor(root->right) > 0) {

            root->right =
                rightRotate(root->right);

            return leftRotate(root);
        }

        return root;
    }

    AVLNode* search(AVLNode* node,
                int id,
                int& steps) {

        if (node == nullptr)
            return nullptr;

        steps++;

        if (node->book.id == id)
            return node;

        if (id < node->book.id)
            return search(node->left,
                          id,
                          steps);

        return search(node->right,
                      id,
                      steps);
    }
    void inorder(AVLNode* node) {

        if (node == nullptr)
            return;

        inorder(node->left);

        cout << "ID: "
             << node->book.id
             << " | Title: "
             << node->book.title
             << " | Author: "
             << node->book.author
             << endl;

        inorder(node->right);
    }

    void rangeSearch(AVLNode* node,
                     int low,
                     int high) {

        if (node == nullptr)
            return;

        if (node->book.id > low)
            rangeSearch(node->left,
                        low,
                        high);

        if (node->book.id >= low &&
            node->book.id <= high)

            cout << node->book.id
                 << " - "
                 << node->book.title
                 << endl;

        if (node->book.id < high)
            rangeSearch(node->right,
                        low,
                        high);
    }

    void closestID(AVLNode* node,
                   int target,
                   int& closest) {

        if (node == nullptr)
            return;

        if (abs(node->book.id - target)
            < abs(closest - target))

            closest = node->book.id;

        if (target < node->book.id)
            closestID(node->left,
                      target,
                      closest);

        else if (target > node->book.id)
            closestID(node->right,
                      target,
                      closest);
    }

public:
    AVL() {
        root = nullptr;
    }

    void insert(Book b) {
        root = insert(root, b);
    }

    void remove(int id) {
        root = deleteNode(root, id);
    }

    void display() {
        inorder(root);
    }

    void searchBook(int id) {

        int steps = 0;

        AVLNode* result =
            search(root, id, steps);

        if (result) {

            cout << "Book Found\n";
            cout << result->book.title << endl;
        }

        else {
            cout << "Book Not Found\n";
        }

        cout << "Steps = "
             << steps << endl;
    }

    void printRange(int low, int high) {
        rangeSearch(root, low, high);
    }

    void findClosest(int target) {

        if (root == nullptr) {

            cout << "Tree Empty\n";
            return;
        }

        int closest = root->book.id;

        closestID(root,
                  target,
                  closest);

        cout << "Closest ID = "
             << closest << endl;
    }

    int getHeight() {
        return getHeight(root);
    }
};

//MAIN

int main() {

    Problem1 bstRandom, bstSorted;

    AVL avlRandom, avlSorted;

    //  RANDOM DATA

    Book randomBooks[] = {

        {100,"C++","Eman"},
        {90,"Java","Mariem"},
        {150,"DS","Sara"},
        {50,"Python","Salma"},
        {75,"Network","Ali"},
        {125,"Database","Nour"},
        {25,"OS","Malak"},
        {60,"AI","Omar"},
        {110,"Math","Hassan"},
        {140,"Physics","Laila"},
        {160,"ML","Khaled"},
        {170,"Security","Yara"},
        {30,"Web","Alaa"},
        {45,"OOP","Heba"},
        {55,"Logic","Mostafa"},
        {65,"Linux","Ziad"},
        {85,"Algorithms","Noha"},
        {95,"Design","Mina"},
        {115,"Management","Youssef"},
        {135,"DBMS","Dina"}
    };

    //  SORTED DATA

    Book sortedBooks[] = {

        {10,"A","A"},
        {20,"B","B"},
        {30,"C","C"},
        {40,"D","D"},
        {50,"E","E"},
        {60,"F","F"},
        {70,"G","G"},
        {80,"H","H"},
        {90,"I","I"},
        {100,"J","J"},
        {110,"K","K"},
        {120,"L","L"},
        {130,"M","M"},
        {140,"N","N"},
        {150,"O","O"},
        {160,"P","P"},
        {170,"Q","Q"},
        {180,"R","R"},
        {190,"S","S"},
        {200,"T","T"}
    };

    // insert

    for (int i = 0; i < 20; i++) {

        bstRandom.insert(randomBooks[i]);
        avlRandom.insert(randomBooks[i]);

        bstSorted.insert(sortedBooks[i]);
        avlSorted.insert(sortedBooks[i]);
    }

    // display

    cout << "\n========== BST RANDOM ==========\n";
    bstRandom.display();

    cout << "\n========== AVL RANDOM ==========\n";
    avlRandom.display();

    // search

    cout << "\n========== SEARCH COMPARISON ==========\n";

    cout << "\nBST Search:\n";
    bstSorted.searchBook(200);

    cout << "\nAVL Search:\n";
    avlSorted.searchBook(200);

    // delete

    cout << "\n========== DELETE ==========\n";

    bstRandom.remove(45);
    avlRandom.remove(45);

    cout << "Book 45 Deleted\n";

    // range search

    cout << "\n========== RANGE SEARCH ==========\n";

    cout << "\nBST:\n";
    bstRandom.printRange(100, 150);

    cout << "\nAVL:\n";
    avlRandom.printRange(100, 150);

    // CLOSEST id

    cout << "\n========== CLOSEST ID ==========\n";

    cout << "\nBST:\n";
    bstRandom.findClosest(24);

    cout << "\nAVL:\n";
    avlRandom.findClosest(24);

    //  HEIGHT COMPARISON

    cout << "\n========== HEIGHT COMPARISON ==========\n";

    cout << "\nBST Random Height = "
         << bstRandom.getHeight();

    cout << "\nAVL Random Height = "
         << avlRandom.getHeight();

    cout << "\nBST Sorted Height = "
         << bstSorted.getHeight();

    cout << "\nAVL Sorted Height = "
         << avlSorted.getHeight();

    cout << endl;

    return 0;
}