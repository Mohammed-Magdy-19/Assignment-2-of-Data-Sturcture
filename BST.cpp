#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
using namespace std;

struct Book{
    int id;
    string title;
    string author;
};
struct  Node{
    Book book;
    Node*left;
    Node*right;
    Node(Book b) {
        book=b;
        left=right=nullptr;
    }
};
 class BST {
 private:
 Node*root;

    //insert
    Node*insert(Node*node,Book b) {
        if (node==nullptr) {
            return new Node(b);
        }
        if (b.id<node->book.id) {
            node->left=insert(node->left,b);
        }else if (b.id>node->book.id) {
            node->right=insert(node->right,b);
        }
        return node;

    }
    //Search
    Node*search(Node*node,int id ,int &steps) {
        steps++;
        if (node==nullptr||node->book.id==id) {
            return node;
        }if (id<node->book.id) {
            return search(node->left,id,steps);
        }else {
            return search (node->right,id,steps);
        }

    }
    //inorder display
    void inorder(Node*node) {
        if (node==nullptr) return;
        inorder(node->left);
        cout<<" ID : "<<node->book.id
        <<" |Title : "<<node->book.title
        <<" |Author : "<<node->book.author<<endl;
        inorder(node->right);
    }
    //findmin
    Node*findmin(Node*node) {
        while (node->left!=nullptr) {
            node=node->left;
        }
        return node;
    }
    //Delete
    Node*deletenode(Node*node,int id) {
        if (node==nullptr)return nullptr;

        if (id<node->book.id) {
            node->left=deletenode(node->left,id);
        }else if (id>node->book.id){
            node->right=deletenode(node->right,id);
        }else {
            if (node->left==nullptr&&node->right==nullptr) {
                delete node;
                return nullptr;
            }else if (node->left==nullptr) {
                Node*temp=node->right;
                delete node;
                return temp;
            }
            else if (node->right==nullptr) {
                Node*temp=node->left;
                delete node;
                return temp;
            }else {
                Node*temp=findmin(node->right);
                node->book=temp->book;
                node->right=deletenode(node->right,temp->book.id);

            }


        }
        return node;
    }
    //range search
    void rangesearch(Node*node,int low,int high) {
        if (node==nullptr)return;
        if (node->book.id>low) {
            rangesearch(node->left,low,high);
        }
        if (node->book.id>=low&&node->book.id<=high) {
            cout<<" ID : "<<node->book.id<<" Title : "<< node->book.title<<endl;
        }
        if (node->book.id<high) {
            rangesearch(node->right,low,high);
        }
    }

    //close id
    void closeid(Node*node,int target,int&closest) {
        if (node==nullptr)return;
        if (abs(node->book.id-target)<abs(closest-target))
            closest=node->book.id;
        if (target<node->book.id)
            closeid(node->left,target,closest);
        else if (target>node->book.id)
            closeid(node->right,target,closest);
    }
    //hight
    int height(Node*node){
    if (node==nullptr)
    return 0;
    int leftheight=height(node->left);
    int rightheight=height(node->right);
        return max(leftheight,rightheight)+1;


}
    public:
    BST() {
        root=nullptr;
    }
    //insert
    void insert(Book b) {
        root=insert(root,b);
    }
    //search
    void search(int id) {
        int steps=0;
        Node*result=search(root,id,steps);
        if (result){
            cout<<"Book Found\n"<<result->book.title<<endl;
            cout<<"Steps = "<<steps<<endl;
        }else {
            cout<<"Book Not Found\n";
            cout<<"Steps = "<<steps<<endl;
        }
    }
    //Display
    void display() {
        inorder(root);
    }
    //delete
    void deletebook(int id) {
        root=deletenode(root,id);
    }
    //range
    void printrange(int low,int high) {
        rangesearch(root,low,high);
    }
    //close
    void findclose(int target) {
        if (root==nullptr) {
            cout<<"Tree is empty\n";
            return;
        }
        int closest=root->book.id;
        closeid(root,target,closest);
        cout<<"Closest Id to: "<<target<<"is: "<<closest<<endl;
    }

    //hight
    int gethight() {
        return height(root);
    }



};



int main() {
    BST randomtree;
BST sortedtree;


// RANDOM TREE

randomtree.insert({100,"C++","Eman"});
randomtree.insert({90,"Java","Mariem"});
randomtree.insert({150,"DS","Sara"});
randomtree.insert({50,"Python","Salma"});
randomtree.insert({75,"Network","Ali"});
randomtree.insert({125,"Database","Nour"});
randomtree.insert({25,"OS","Malak"});
randomtree.insert({60,"AI","Omar"});
randomtree.insert({110,"Math","Hassan"});
randomtree.insert({140,"Physics","Laila"});
randomtree.insert({160,"ML","Khaled"});
randomtree.insert({170,"Security","Yara"});
randomtree.insert({30,"Web","Alaa"});
randomtree.insert({45,"OOP","Heba"});
randomtree.insert({55,"Logic","Mostafa"});
randomtree.insert({65,"Linux","Ziad"});
randomtree.insert({85,"Algorithms","Noha"});
randomtree.insert({95,"Design","Mina"});
randomtree.insert({115,"Management","Youssef"});
randomtree.insert({135,"DBMS","Dina"});

cout<<"----------------------------------------------------------------------";
// SORTED TREE

sortedtree.insert({10,"A","A"});
sortedtree.insert({20,"B","B"});
sortedtree.insert({30,"C","C"});
sortedtree.insert({40,"D","D"});
sortedtree.insert({50,"E","E"});
sortedtree.insert({60,"F","F"});
sortedtree.insert({70,"G","G"});
sortedtree.insert({80,"H","H"});
sortedtree.insert({90,"I","I"});
sortedtree.insert({100,"J","J"});
sortedtree.insert({110,"K","K"});
sortedtree.insert({120,"L","L"});
sortedtree.insert({130,"M","M"});
sortedtree.insert({140,"N","N"});
sortedtree.insert({150,"O","O"});
sortedtree.insert({160,"P","P"});
sortedtree.insert({170,"Q","Q"});
sortedtree.insert({180,"R","R"});
sortedtree.insert({190,"S","S"});
sortedtree.insert({200,"T","T"});
    cout<<"----------------------------------------------------------------------";

// display

cout << "Random Tree:\n";
randomtree.display();

cout << "\nSorted Tree:\n";
sortedtree.display();
    cout<<"----------------------------------------------------------------------";

// search comparison

cout << "\nSearch in Random Tree:\n";
randomtree.search(50);

cout << "\nSearch in Sorted Tree:\n";
sortedtree.search(50);

    cout<<"----------------------------------------------------------------------";
// delete from random

cout << "\nDelete ID 45 from Random Tree\n";
randomtree.deletebook(45);

cout << "After deletion:\n";
randomtree.display();

    cout<<"----------------------------------------------------------------------";
//range search from random

cout << "\nBooks between 100 and 150 in random tree:\n";
randomtree.printrange(100,150);
    cout<<"----------------------------------------------------------------------";

// close id from random

cout << "\nClosest ID to 24 in random tree:\n";
randomtree.findclose(24);

    cout<<"----------------------------------------------------------------------";
// height comparison

cout << "\nRandom Height = " << randomtree.gethight() << endl;
cout << "Sorted Height = " << sortedtree.gethight() << endl;
    cout<<"----------------------------------------------------------------------";
}

